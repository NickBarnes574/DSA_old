# required options
CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla

# add header files to the compile path
CFLAGS += -I ./include/

DSA_OBJ = \
src/exit_codes.o \
src/linked_lists/singly_linked_list.o\
src/linked_lists/doubly_linked_list.o \
src/linked_lists/circular_singly_linked_list.o \
src/array_list.o \
src/void_pointer_functions.o \
src/utilities/comparison_helpers.o \
src/utilities/destroy_helpers.o

# individual test files
SINGLY_LINKED_LIST_TESTS = test/linked_lists/singly_linked_list_tests.o
DOUBLY_LINKED_LIST_TESTS = test/linked_lists/doubly_linked_list_tests.o
CIRCULAR_SINGLY_LINKED_LIST_TESTS = test/linked_lists/circular_singly_linked_list_tests.o
ARRAY_LIST_TESTS = test/array_list_tests.o

# combile all the tests into one list
ALL_TESTS = test/dsa_test_all.o \
$(SINGLY_LINKED_LIST_TESTS) \
$(DOUBLY_LINKED_LIST_TESTS) \
$(CIRCULAR_SINGLY_LINKED_LIST_TESTS) \
$(ARRAY_LIST_TESTS)

# make a library
.PHONY: library
library: libdsa.a

# makes a profile
.PHONY: profile
profile: CFLAGS += -pg
profile: clean
profile: libdsa.a dsa.exe

# makes a debug version of the library
.PHONY: debug
debug: CFLAGS += -g -gstabs -O0
debug: libdsa.a

# delete the library and all the .o files
.PHONY: clean
clean:
	$(RM) libdsa.a
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -perm /111 -exec rm -f {} \;

libdsa.a: ARFLAGS += -sU
libdsa.a: $(DSA_OBJ) # the presence of this rule prevents make from deleting the .o automatically, which leaves it for dependency checking later
libdsa.a: libdsa.a($(DSA_OBJ))

# creates and runs tests using valgrind
.PHONY: valcheck
valcheck: CFLAGS += -g
valcheck: test/dsa_test
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^

# creates and runs tests
.PHONY: check
check: CFLAGS += -g
check: test/dsa_test
	./$^

# Comprehensive test testing all dependencies
test/dsa_test: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit
test/dsa_test: $(ALL_TESTS)
	$(CC) $(CFLAGS) $(ALL_TESTS) libdsa.a $(CHECKLIBS) -o test/dsa_test

# Modules under test
test/dsa_test: libdsa.a
