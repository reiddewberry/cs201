OBJS = integer.o real.o sll.o dll.o stack.o queue.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : test-sll test-dll test-stack test-queue

test-sll : test-sll.c sll.h integer.h integer.o sll.o
	gcc $(LOPTS) test-sll.c integer.o sll.o -o test-sll

test-dll : test-dll.c dll.h dll.o integer.o
	gcc $(LOPTS) test-dll.c integer.o dll.o -o test-dll

test-stack : test-stack.c stack.h integer.h dll.o integer.o stack.o
	gcc $(LOPTS) test-stack.c integer.o dll.o stack.o -o test-stack

test-queue : test-queue.c integer.h sll.o queue.o integer.o
	gcc $(LOPTS) test-queue.c integer.o sll.o queue.o -o test-queue

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

valgrind  : all
	echo testing singly-linked list
	valgrind ./test-sll


test : all
	echo testing singly-linked list
	./test-sll
	echo
	echo testing doubly-linked list
	./test-dll
	echo
	echo testing stack
	./test-stack
	echo
	echo testing queue
	./test-queue
	echo

clean    :
	rm -f $(OBJS) test-*.o *.o test-stack test-queue test-sll test-dll

# Using test server test files

#test-sll : sll-0-0.c sll.h integer.h integer.o sll.o
#	gcc $(LOPTS) sll-0-0.c integer.o sll.o -o test-sll

#test-dll : dll-0-0.c dll.h real.h real.o dll.o integer.o
#	gcc $(LOPTS) dll-0-0.c integer.o real.o dll.o -o test-dll

#test-stack : stack-0-0.c stack.h integer.h dll.o integer.o stack.o
#	gcc $(LOPTS) stack-0-0.c integer.o dll.o stack.o -o test-stack

#test-queue : queue-0-0.c queue.h sll.h integer.h integer.o
#	gcc $(LOPTS) queue-0-0.c integer.o -o test-queue


