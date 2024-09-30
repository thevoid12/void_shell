# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source directory
SRC_DIR = src

# Target executable name
TARGET = void_shell

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/execute_ls.c $(SRC_DIR)/execute_pwd.c $(SRC_DIR)/execute_cd.c $(SRC_DIR)/execute_exit.c $(SRC_DIR)/execute_touch.c

# Object files (for each source file)
OBJS = $(SRCS:.c=.o)

# Default target: build the executable
all: $(TARGET)

# Rule for linking object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling each .c file to .o file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule: remove object files and the executable
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
