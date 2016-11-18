#You must have a Makefile in the root directory
#In the Makefile you will have two targets. The
#first target is called all and the second target
#is called rshell. Both of these targets will
#compile your program using g++ with the flags: 
#-Wall -Werror -ansi -pedantic .

#Compiler
CC=g++ 
CFLAGS=-Wall -Werror -ansi -pedantic -I$(HEADERDIR)

#Name of executable
TARGET=./bin/rshell

#Source and object dir
OBJDIR=bin
SRCDIR=src
HEADERDIR=header

#Files and directories
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)


#Targets
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(SOURCES) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(OBJDIR)