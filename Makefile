# Compiler and Flags
CC      := gcc
CFLAGS  := -Wall -Wextra -g

# Target Name
TARGET  := periclesshell

# List your source files manually or let wildcard find them
SRCS    := main.c pericles_fs.c stdpericles.c
# This converts .c filenames to .o filenames
OBJS    := $(SRCS:.c=.o)

# Default Rule
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "--- Build Complete: Run with ./periclesshell ---"

# Compile .c files into .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "--- Workspace Cleaned ---"

.PHONY: all clean
