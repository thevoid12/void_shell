# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source directory
SRC_DIR = src

# Target executable name
TARGET = void_shell

# Source files
SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/execute_ls.c $(SRC_DIR)/execute_pwd.c $(SRC_DIR)/execute_cd.c $(SRC_DIR)/execute_exit.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule for compiling .c to .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/headers.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

.PHONY: all clean
