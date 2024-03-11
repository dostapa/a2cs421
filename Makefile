src = src/main.c src/functions.c
obj = $(src:.c=.o)
inc = -I./include
CC = gcc

# Path: Makefile
# Compile the source files
all: main clean

main: $(obj)
	$(CC) -o a2cs421 $(obj) $(inc)

clean:
	rm -f $(obj)