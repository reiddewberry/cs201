OBJS = integer.o real.o sll.o dll.o stack.o queue.o
OBJSH = integer.h real.h sll.h dll.h stack.h queue.h
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-bst bst-1-3 test-heap heapsort

test-bst : test-bst.c bst.h queue.h sll.h integer.h bst.o queue.o sll.o integer.o
	gcc $(LOPTS) test-bst.c bst.o queue.o sll.o integer.o -o test-bst

bst-1-3 : bst-1-3.c bst.h queue.h sll.h integer.h bst.o queue.o sll.o integer.o
	gcc $(LOPTS) bst-1-3.c bst.o queue.o sll.o integer.o -o bst-1-3

test-heap : test-heap.c heap.h bst.h queue.h stack.h sll.h dll.h integer.h heap.o bst.o queue.o stack.o sll.o dll.o integer.o
	gcc $(LOPTS) test-heap.c heap.o bst.o queue.o stack.o sll.o dll.o integer.o -o test-heap

heapsort : heapsort.c heap.h bst.h string.h scanner.h $(OBJSH) heap.o bst.o string.o scanner.o $(OBJS)
	gcc $(LOPTS) heapsort.c heap.o bst.o $(OBJS) string.o scanner.o -o heapsort

test-sll : test-sll.c sll.h integer.h integer.o sll.o
	gcc $(LOPTS) test-sll.c integer.o sll.o -o test-sll

test-dll : test-dll.c dll.h dll.o integer.o
	gcc $(LOPTS) test-dll.c integer.o dll.o -o test-dll

test-stack : test-stack.c stack.h integer.h dll.o integer.o stack.o
	gcc $(LOPTS) test-stack.c integer.o dll.o stack.o -o test-stack

test-queue : test-queue.c integer.h sll.o queue.o integer.o
	gcc $(LOPTS) test-queue.c integer.o sll.o queue.o -o test-queue

heap.o : heap.c heap.h
	gcc $(OOPTS) heap.c

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

valgrind  : test-heap
	echo testing singly-linked list
	valgrind ./test-heap

test : test-heap
	echo testing doubly-linked list
	./test-heap
	echo

clean    :
	rm -f $(OBJS) test-*.o *.o test-sll test-dll test-stack test-queue test-bst test-heap heapsort heap-0-0 heap-0-1 heap-0-2 bst-0-0 bst-1-3

# Using test server test files

#test-sll : sll-0-0.c sll.h integer.h integer.o sll.o
#	gcc $(LOPTS) sll-0-0.c integer.o sll.o -o test-sll

#test-dll : dll-0-0.c dll.h real.h real.o dll.o integer.o
#	gcc $(LOPTS) dll-0-0.c integer.o real.o dll.o -o test-dll

#test-stack : stack-0-0.c stack.h integer.h dll.o integer.o stack.o
#	gcc $(LOPTS) stack-0-0.c integer.o dll.o stack.o -o test-stack

#test-queue : queue-0-0.c queue.h sll.h integer.h integer.o
#	gcc $(LOPTS) queue-0-0.c integer.o -o test-queue


