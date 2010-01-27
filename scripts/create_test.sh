#!/bin/bash

# check arguments
if [ $# -ne 2 ] ; then
    echo 
    echo 'ERROR: Wrong argument count.'
    echo 'Usage:' $0 '<class name>' '<header file>'
    echo 
    exit 1
fi

# check if in the rigth place
if [ ! -d "tests" ]; then
    echo 'ERROR: tests directory not found'
    echo 'Please run this script from the parent directory of the
project.' 
    exit 1
fi

CLASSNAME="$1"
HEADERFILE="$2"
TESTNAME=${CLASSNAME}_test
TESTFILE=tests/${TESTNAME}.cpp


if [ -f ${TESTFILE} ] ; then
    echo 'Error: file '$TESTNAME' already exists.'
    echo 'Please remove it before continuing.'
    exit 1
fi

function write_includes()
{
    echo
    echo '#include <gtest/gtest.h>'
    echo '#include "'$HEADERFILE'"'
    echo 
}

function write_test_class()
{
    echo 'namespace '
    echo '{'
    echo '  // The fixture for testing class '$CLASSNAME 
    echo '  class '$TESTNAME
    echo '    : public ::testing::Test '
    echo '  {'
    echo '  protected:'
    echo '    // You can remove any or all of the following functions if its body'
    echo '    // is empty.'
    echo ''
    echo '    ' $TESTNAME '() '
    echo '    {'
    echo '      // You can do set-up work for each test here.'
    echo '    }'
    echo 
    echo '    virtual ~'$TESTNAME'() '
    echo '    {'
    echo "      // You can do clean-up work that doesn't throw exceptions here."
    echo '    }'
    echo ''
    echo '    // If the constructor and destructor are not enough for setting up'
    echo '    // and cleaning up each test, you can define the following methods:'
    echo 
    echo '    virtual void SetUp() '
    echo '    {'
    echo '      // Code here will be called immediately after the constructor (right '
    echo '      // before each test).'
    echo '    }'
    echo 
    echo '    virtual void TearDown() '
    echo '    {'
    echo '      // Code here will be called immediately after each test (right'
    echo '      // before the destructor).'
    echo '    }'
    echo ''
    echo '    // Objects declared here can be used by all tests in the test case'
    echo '    // for '$CLASSNAME
    echo '  };'
    echo ''
    echo '  // Tests default constructor'
    echo '  TEST_F('$TESTNAME', default_constructor) '
    echo '  {'
    echo '   '$CLASSNAME' var;'
    echo '  }'
    echo 
    echo '}  // namespace'
    echo 
}

function write_main()
{
    echo 
    echo 'int'
    echo 'main(int argc, char **argv)'
    echo '{'
    echo '  ::testing::InitGoogleTest(&argc, argv);'
    echo '  return RUN_ALL_TESTS();'
    echo '}'
}

function add_to_makefile()
{
    echo 
    echo 'bin_PROGRAMS += '$TESTNAME
    echo ${TESTNAME}_SOURCES '=' ${TESTNAME}.cpp
}

# create file
write_includes > $TESTFILE
write_test_class >> $TESTFILE
write_main >> $TESTFILE

add_to_makefile >> tests/Makefile.am
# add to Makefile.am 
