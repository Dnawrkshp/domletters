# makefile template from
# https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html

# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#	-g	adds debugging information to the executable file
#	-Wall turns on most, but not all, compiler warnings
CFLAGS	= -g -Wall

# the build target executable:
TARGET = domletters

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
	$(RM) $(TARGET)
