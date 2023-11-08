CC = gcc
CFLAGS = -std=c99 -Wall -Werror 
DEBUG = gdb
FILEOUT = tree.out
SOURCES = tree.c main.c

all: tree.out 

tree.out:
	$(CC) $(CFLAGS) $(SOURCES)  -o $(FILEOUT)
	
clean:
	rm -f *.out
debug:
	$(CC) $(CFLAGS) -g $(SOURCES)
	sudo $(DEBUG) $(FILEOUT)
cmp:
	$(CC) $(CFLAGS) $(SOURCES) -o $(FILEOUT)
run:
	./$(FILEOUT) $(FILE)
	
test:
	valgrind --tool=memcheck ./$(FILEOUT)
	
