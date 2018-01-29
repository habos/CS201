CC=gcc
CFLAGS=-Wall -Wextra -c -std=c99
LDFLAGS=

SRCS=sll.c integer.c slltest.c
OBJS=$(SRCS:.c=.o)
EXEC=tester

all : $(EXEC) $(SRCS)

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean valgrind test
clean :
	rm -f $(EXEC) $(OBJS)
valgrind : all
	echo testing singly-linked list
	valgrind ./test-sll
	echo
test : all
	echo testing singly-linked list
	./test-sll
	echo

