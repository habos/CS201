CC=gcc
CFLAGS=-Wall -Wextra -c -std=c99 -g
LDFLAGS=

SRCS=main.c bst.c queue.c sll.c integer.c heap.c stack.c dll.c options.c string.c real.c scanner.c
OBJS=$(SRCS:.c=.o)
EXEC=heapsort

all : $(EXEC) $(SRCS)

$(EXEC) : $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean test valgrind
clean :
	rm -f $(EXEC) $(OBJS)

test : $(EXEC)
	./$(EXEC)

valgrind : $(EXEC)
	valgrind ./$(EXEC)
