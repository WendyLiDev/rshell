CC=g++

CFLAGS=-c -Wall -Werror

all: assignment2

assignment2: And.o Operator.o main.o Command.o Or.o Semicolon.o -o assignment2

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Command.o: Command.cpp
	$(CC) $(CFLAGS) Command.cpp
	
And.o: And.cpp
	$(CC) $(CFLAGS) And.cpp

Or.o: Or.cpp
	$(CC) $(CFLAGS) Or.cpp
	
Semicolon.o: Semicolon.cpp
	$(CC) $(CFLAGS) Selicolon.cpp

Operator.o: Operator.cpp
	$(CC) $(CFLAGS) Operator.cpp

clean:
	rm *o assignment2