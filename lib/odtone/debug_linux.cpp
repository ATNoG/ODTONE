//==============================================================================
// Brief   : Debug Helpers (platform dependent implementation - linux)
// Authors : Bruno Santos <bsantos@av.it.pt>
//------------------------------------------------------------------------------
// ODTONE - Open Dot Twenty One
//
// Copyright (C) 2009-2012 Universidade Aveiro
// Copyright (C) 2009-2012 Instituto de Telecomunicações - Pólo Aveiro
//
// This software is distributed under a license. The full license
// agreement can be found in the file LICENSE in this distribution.
// This software may not be copied, modified, sold or distributed
// other than expressed in the named license agreement.
//
// This software is distributed without any warranty.
//==============================================================================

#include <odtone/debug.hpp>
#include <odtone/list_node.hpp>
#include <boost/utility.hpp>
#include <boost/assert.hpp>
#include <boost/array.hpp>
#include <cstdio>
#include <cstring>
#include <limits.h>
#include <execinfo.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

///////////////////////////////////////////////////////////////////////////////
namespace {

using namespace odtone;
using odtone::uint;
using odtone::ulong;

///////////////////////////////////////////////////////////////////////////
class process {
	process(const process&) = delete;
	process& operator=(const process&) = delete;

public:
	process(process&& ps);
	process& operator=(process&& ps);

public:
	struct console {
		console(int _in = -1, int _out = -1, int _err = -1)
			: in(_in), out(_out), err(_err)
		{ }

		int in;
		int out;
		int err;
	};

	process();
	process(const char* path, const console& io = console());
	template<size_t N>
	process(const char* path, const boost::array<const char*, N>& args, const console& io = console());
	~process();

private:
	int _pid;
	int _stdin;
	int _stdout;
	int _stderr;
};

process::process(process&& ps)
	: _pid(-1), _stdin(-1), _stdout(-1), _stderr(-1)
{
	std::swap(_pid, ps._pid);
	std::swap(_stdin, ps._stdin);
	std::swap(_stdout, ps._stdout);
	std::swap(_stderr, ps._stderr);
}

process& process::operator=(process&& ps)
{
	if (this != &ps) {
		std::swap(_pid, ps._pid);
		std::swap(_stdin, ps._stdin);
		std::swap(_stdout, ps._stdout);
		std::swap(_stderr, ps._stderr);
	}
	return *this;
}

process::process()
	: _pid(-1), _stdin(-1), _stdout(-1), _stderr(-1)
{
}

process::process(const char* path, const console& io)
	: _stdin(io.in), _stdout(io.out), _stderr(io.err)
{
	_pid = ::fork();

	if (!_pid) {
		if (_stdin >= 0 && _stdin != 0)
			::dup2(_stdin, 0);
		if (_stdout >= 0 && _stdout != 1)
			::dup2(_stdout, 1);
		if (_stderr >= 0 && _stderr != 2)
			::dup2(_stderr, 2);

		::execlp(path, path, (const char*) 0);
		std::abort();
	}
}

template<size_t N>
process::process(const char* path, const boost::array<const char*, N>& args, const console& io)
	: _stdin(io.in), _stdout(io.out), _stderr(io.err)
{
	_pid = ::fork();

	if (!_pid) {
		const char* cargs[N+2];

		if (_stdin >= 0 && _stdin != 0)
			::dup2(_stdin, 0);
		if (_stdout >= 0 && _stdout != 1)
			::dup2(_stdout, 1);
		if (_stderr >= 0 && _stderr != 2)
			::dup2(_stderr, 2);

		cargs[0] = path;
		for (size_t i = 0; i < N; ++i)
			cargs[i + 1] = args[i];
		cargs[N+1] = nullptr;

		::execvp(path, const_cast<char**>(cargs));
		std::abort();
	}
}

process::~process()
{
	if (_stdin >= 0 && _stdin != 0)
		::close(_stdin);
	if (_stdout >= 0 && _stdout != 1)
		::close(_stdout);
	if (_stderr >= 0 && _stderr != 2)
		::close(_stderr);
}

///////////////////////////////////////////////////////////////////////////
class module {
	friend class module_list;

public:
	module(const char* path, size_t start, size_t end, const char prot[4])
		: _path(path), _start(start), _end(end), _fdin(-1), _fdout(-1)
	{
		_prot[0] = prot[0];
		_prot[1] = prot[1];
		_prot[2] = prot[2];
		_prot[3] = prot[3];
		_prot[4] = '\0';
	}

	const char* name() const
	{
		uint p = 0;

		for(uint i = 0; _path[i] != '\0'; ++i) {
			if (_path[i] == '/')
				p = i + 1;
		}
		return _path + p;
	}

	const char* path() const	{ return _path; }
	size_t start() const		{ return _start; }
	size_t end() const			{ return _end; }
	const char* prot()			{ return _prot; }

	bool operator==(size_t address)
	{
		if (address < _start || address > _end)
			return false;
		return true;
	}

	bool operator!=(size_t address)
	{
		return !(*this == address);
	}

	void print_addr2line(uint i, void* address)
	{
		const char* name;
		const char* file;
		char buffer[512];
		ssize_t len;
		size_t n;
		char* pn = 0;
		char* pf = 0;

		if (!init_addr2line()) {
			std::fprintf(stderr, "%02u %016lX%*c%s\n", i, ulong(address), 24, ' ', this->name());
			return;
		}

		len = sprintf(buffer, "%lx\n", ulong(address));
		if (::write(_fdout, buffer, len) < 0)
			std::fprintf(stderr, "%02u %016lX\n", i, ulong(address));

		n = 0;
		do {
			len = ::read(_fdin, buffer + n, sizeof(buffer) - n);
			if (len <= 0)
				std::fprintf(stderr, "%02u %016lX\n", i, ulong(address));

			if (!pn) {
				pn = std::strchr(buffer + n, '\n');
				pf = std::strchr(pn + 1, '\n');
			} else {
				pf = std::strchr(buffer + n, '\n');
			}

			n += len;

		} while (!pf);

		*pn = '\0';
		*pf = '\0';

		pf = std::strrchr(++pn, '/');

		name = buffer;
		file = pf ? pf + 1 : pn;

		if (std::strcmp(file, "??:0") == 0) {
			file = this->name();
		}

		if (std::strcmp(name, "??") == 0) {
			std::fprintf(stderr, "%02u %016lX%*c[%s]\n", i, ulong(address), 24, ' ', file);

		} else {
			n = 40 - std::strlen(name);
			n = (n > 40) ? 0 : n;
			std::fprintf(stderr, "%02u %s%*c[%s]\n", i, name, int(n), ' ', file);
		}
	}

private:
	bool init_addr2line()
	{
		int fdin[2];
		int fdout[2];
		struct stat s;

		if (_fdin != -1)
			return true;

		if ((::lstat(_path, &s) < 0) || !S_ISREG(s.st_mode))
			return false;

		if (!::pipe(fdin) && !::pipe(fdout)) {
			boost::array<const char*, 4> args;

			::fcntl(fdin[1], F_SETFD, FD_CLOEXEC);
			::fcntl(fdout[0], F_SETFD, FD_CLOEXEC);

			args[0] = "-f";
			args[1] = "-C";
			args[2] = "-e";
			args[3] = _path;
			process ps("addr2line", args, process::console(fdin[0], fdout[1]));

			_fdin = fdout[0];
			_fdout = fdin[1];

			return true;
		}

		return false;
	}

private:
	list_node   _node;
	const char* _path;
	size_t      _start;
	size_t      _end;
	char        _prot[5];
	int         _fdin;
	int         _fdout;
};

class module_list {
public:
	typedef uint size_type;

	class iterator {
	public:
		iterator(list_node* node)
		{
			_prev = _ptr = parent_of<module>(node, &module::_node);
		}

		module* operator++()
		{
			_prev = _ptr;
			_ptr = parent_of<module>(_ptr->_node.front(), &module::_node);
			return _ptr;
		}

		module* operator++(int)
		{
			_prev = _ptr;
			_ptr = parent_of<module>(_ptr->_node.front(), &module::_node);
			return _prev;
		}

		module& operator*() { return *_ptr; }
		module* operator->() { return _ptr; }

		bool operator==(const iterator& i) { return _prev == i._prev; }
		bool operator!=(const iterator& i) { return _prev != i._prev; }

	private:
		module* _ptr;
		module* _prev;
	};

	module_list() : _count(0)
	{
		_list.init();
	}

	size_type count()	{ return _count; }
	iterator begin()	{ return iterator(_list.front()); }
	iterator end()		{ return iterator(_list.back()); }

	void insert(module* module)
	{
		_list.push_back(&module->_node);
		_count += 1;
	}

	module* find(size_t address)
	{
		for (iterator i = begin(); i != end(); i++) {
			if (*i == address)
				return &(*i);
		}
		return nullptr;
	}

private:
	list_node _list;
	size_type _count;
};

///////////////////////////////////////////////////////////////////////////
void* crash_alloc(size_t n)
{
	static uchar* start = 0;
	static uchar* end = 0;

	const size_t k_alignment_adjust = sizeof(ulong)-1;
	void* tmp;

	if (size_t(end - start) < n) {
		size_t sz = ::sysconf(_SC_PAGESIZE);

		if (n > sz) {
			sz = (n + (sz-1)) & ~(sz-1);
		}
		start = (uchar*) ::mmap(nullptr, sz, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_GROWSDOWN, -1, 0);
		if (start == (void*) -1) {
			return nullptr;
		}
		end = start + sz;
	}
	tmp = start;
	start += (n + k_alignment_adjust) & ~k_alignment_adjust;

	return tmp;
}

void build_module_list(module_list& ml)
{
	const size_t k_page_size = ::sysconf(_SC_PAGESIZE);
	ulong start, end, rd, dump, pos = 0;
	char path[4096];
	char prot[4];
	char* buffer;
	char* endl;
	char* name;
	module* m;
	int fd;

	if (!(buffer = (char*) crash_alloc(k_page_size)))
		return;

	fd = ::open("/proc/self/maps", O_RDONLY);
	if (fd <= 0)
		return;
	rd = ::read(fd, buffer, k_page_size);
	::close(fd);
	if (rd <= 0)
		return;

	while (pos < rd) {
		endl = buffer + pos;
		size_t len;

		while (++endl != &buffer[rd]) {
			if(*endl == '\n')
				break;
		}
		*endl = '\0';

		path[0] = '\0';
		std::sscanf(&buffer[pos], "%lx-%lx %c%c%c%c %lx %lx:%lx %ld %s",
								  &start, &end, prot + 0, prot + 1, prot + 2, prot + 3,
								  &dump, &dump, &dump, &dump, path);
		pos = (endl - buffer) + 1;
		len = std::strlen(path);
		if (len != 0) {
			name = (char*) crash_alloc(len + 1);
			if (!name)
				return;
			std::memcpy(name, path, len + 1);

			m = new(crash_alloc(sizeof(module))) module(name, start, end, prot);
			if (!m)
				return;
			ml.insert(m);
		}
	}
}

void dump_module_list(module_list& ml)
{
	if (!ml.count())
		return;

	std::printf("\n== modules(%u) ==\n", ml.count());
	for(module_list::iterator i = ml.begin(); i != ml.end(); i++) {
		std::printf("[%08lx-%08lx] %s %s\n",
					(ulong) i->start(), (ulong) i->end(), i->prot(), i->path());
	}
}

void signal_handler(int, siginfo_t* info, void* context)
{
	struct sigcontext* mctx = (struct sigcontext*) &((ucontext_t*) context)->uc_mcontext;
	odtone::crash_ctx ctx;

	memset(&ctx, 0, sizeof(ctx));
	switch(info->si_signo) {
	case SIGFPE:
		ctx.code = odtone::bug_floting_point_exception;
		break;

	case SIGILL:
		ctx.code = odtone::bug_invalid_opcode;
		break;

	case SIGINT:
		ctx.code = odtone::bug_terminal_interrupt;
		break;

	case SIGSEGV:
		ctx.code = odtone::bug_page_fault;
		break;

	case SIGTRAP:
		ctx.code = odtone::bug_breakpoint;
		break;

	default:
		ctx.code = odtone::bug_on;
	}

#ifdef __i386__
	ctx.address = (void*) mctx->eip;
#elif __amd64__
	ctx.address = (void*) mctx->rip;
#endif
	ctx.context = mctx;
	odtone::crash(ctx);
}

void dump_checkpoints()
{
	if (!checkpoint::top())
		return;

	std::fprintf(stderr, "\n"
						 "== checkpoints ==\n");
	for (odtone::checkpoint* i = checkpoint::top(); i; i = i->previous()) {
		std::fprintf(stderr,	"%s (%s:%u)\n", i->expression(), i->file(), i->line());
	}
}

void dump_context(void* context)
{
	struct sigcontext* ctx = (struct sigcontext*) context;

	if (ctx) {
#ifdef __i386__
		std::fprintf(stderr,	"\n"
								"== context ==\n"
								"eax = %08lX  edx = %08lX  ecx = %08lX  ebx = %08lX\n"
								"edi = %08lX  esi = %08lX  ebp = %08lX  esp = %08lX\n"
								"eip = %08lX  eflags = %08lX\n",
								ctx->eax, ctx->edx, ctx->ecx, ctx->ebx,
								ctx->edi, ctx->esi, ctx->ebp, ctx->esp,
								ctx->eip, ctx->eflags);

#elif __amd64__
		std::fprintf(stderr,	"\n"
								"== context ==\n"
								"rax = %016lX  rdx = %016lX  rcx = %016lX  rbx = %016lX\n"
								"rdi = %016lX  rsi = %016lX  rbp = %016lX  rsp = %016lX\n"
								"r8  = %016lX  r9  = %016lX  r10 = %016lX  r11 = %016lX\n"
								"r12 = %016lX  r13 = %016lX  r14 = %016lX  r15 = %016lX\n"
								"rip = %016lX  eflags = %08lX\n",
								ctx->rax, ctx->rdx, ctx->rcx, ctx->rbx,
								ctx->rdi, ctx->rsi, ctx->rbp, ctx->rsp,
								ctx->r8 , ctx->r9 , ctx->r10, ctx->r11,
								ctx->r12, ctx->r13, ctx->r14, ctx->r15,
								ctx->rip, ctx->eflags);
#endif
	}
}

void dump_stack(module_list& ml, void* address)
{
	void* trace[128];
	int cnt, j, i = 0;
	module* m;

	cnt = ::backtrace(trace, 128);
	while (i < cnt && address) {
		if (trace[i] == address)
			break;
		++i;
	}

	j = i;
	if (i < cnt) {
		fprintf(stderr, "\n== stack trace ==\n");
		while (i < cnt) {
			m = ml.find(size_t(trace[i]));
			if (m)
				m->print_addr2line(i - j, trace[i]);
			else
				std::fprintf(stderr, "%02u %016lX\n", i - j, ulong(trace[i]));
			++i;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace */

///////////////////////////////////////////////////////////////////////////////
namespace odtone {

///////////////////////////////////////////////////////////////////////////////

/**
 * Setup the crash handler.
 */
void setup_crash_handler()
{
	struct sigaction handler;

	handler.sa_sigaction = signal_handler;
	handler.sa_flags = SA_SIGINFO;
	sigemptyset(&handler.sa_mask);
	sigaction(SIGFPE, &handler, nullptr);
	sigaction(SIGILL, &handler, nullptr);
	sigaction(SIGINT, &handler, nullptr);
	sigaction(SIGSEGV, &handler, nullptr);
	sigaction(SIGTRAP, &handler, nullptr);
	//SIGSTKFLT
}

/**
 * Handle the crash context.
 * Output the crash infromation and abort the application execution.
 *
 * @param ctx Crash context.
 */
void crash(const crash_ctx& ctx)
{
	module_list ml;
	module* m;

	build_module_list(ml);
	m = ml.find(size_t(ctx.address));

	std::fprintf(stderr,	 "\n"
							 "================================= Crash Dump ==================================\n"
							 "Module : %s\n"
							 "Code   : %s\n",
							 m ? m->path() : "??",
							 k_bug_code_string[ctx.code]);

	if (ctx.file) {
		std::fprintf(stderr, "Function  : %s\n"
							 "File      : %s\n"
							 "Line      : %u\n",
							 ctx.function,
							 ctx.file,
							 ctx.line);
	}

	if (ctx.expression) {
		std::fprintf(stderr, "Expression: %s\n",
							 ctx.expression);
	}

	dump_checkpoints();
	dump_context(ctx.context);
	dump_stack(ml, ctx.address);
	//dump_module_list(ml);

	std::fprintf(stderr,	 "===============================================================================\n"
							 "\n");
	std::abort();
}

///////////////////////////////////////////////////////////////////////////////
} /* namespace odtone */

// EOF ////////////////////////////////////////////////////////////////////////
