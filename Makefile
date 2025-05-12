CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# List of object files
OBJS = main.o cart.o cpu.o ppu.o

# Output binary name
TARGET = gb

# Default target
all: $(TARGET)

# Link object files to create the binary
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f *.o $(TARGET)
