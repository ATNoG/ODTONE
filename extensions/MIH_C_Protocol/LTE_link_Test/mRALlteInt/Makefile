# lines starting with the pound sign are comments.
#
# These things are options that you might need
# to tweak.


# You can modify the below as well, but probably
# won't need to.

CC = gcc

CFLAGS = -Wall -g -I../include/

COMPILE = $(CC) $(CFLAGS) -c

OBJS = mRALlteInt_main.o mRALlteInt_msg.o mRALlteInt_log.o

EXECUTABLE = mRALlteInt

# "all" is the default target. Simply make it point to myprogram.

all: $(EXECUTABLE)

mRALlteInt : mRALlteInt_main.o mRALlteInt_log.o mRALlteInt_msg.o
	$(CC) -o mRALlteInt mRALlteInt_main.o mRALlteInt_log.o mRALlteInt_msg.o

%.o: %.c
	$(COMPILE) -o $@ $<

clean:
	-rm $(OBJS) $(EXECUTABLE)



