#You must have a Makefile in the root directory
#In the Makefile you will have two targets. The
#first target is called all and the second target
#is called rshell. Both of these targets will
#compile your program using g++ with the flags: 
#-Wall -Werror -ansi -pedantic .

CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
EXEC=rshell
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

clean:
	rm -f $(EXEC) $(OBJECTS)
