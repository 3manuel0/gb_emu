CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# List of object files
OBJS = main.o cart.o

# Output binary name
TARGET = main

# Default target
all: $(TARGET)

# Link object files to create the binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f *.o $(TARGET)
