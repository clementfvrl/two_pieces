# TwoPieces RPG Simulator
# Makefile for structured architecture

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
INCLUDES = -Iinclude

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Source files
SRCS = main.c game.c player.c world.c npc.c combat.c save.c time.c event.c services.c
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
TARGET = $(BINDIR)/two_pieces

# Create directories if they don't exist
$(shell mkdir -p $(OBJDIR) $(BINDIR))

.PHONY: all clean run debug install test

# Default target
all: $(TARGET)

# Link executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f *.o two_pieces

# Run the program
run: $(TARGET)
	$(TARGET)

# Debug build with additional flags
debug: CFLAGS += -DDEBUG -O0
debug: clean all

# Install (copy to system path - optional)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# Test build (compile only)
test: all
	@echo "Build successful - Ready to run!"

# Show help
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  clean   - Remove build artifacts"
	@echo "  run     - Build and run the program"
	@echo "  debug   - Build with debug flags"
	@echo "  test    - Test compilation"
	@echo "  help    - Show this help"

# Dependencies (headers)
$(OBJDIR)/main.o: $(INCDIR)/game.h $(INCDIR)/player.h
$(OBJDIR)/game.o: $(INCDIR)/game.h $(INCDIR)/event.h $(INCDIR)/time.h $(INCDIR)/world.h
$(OBJDIR)/player.o: $(INCDIR)/player.h $(INCDIR)/game.h
$(OBJDIR)/world.o: $(INCDIR)/world.h $(INCDIR)/game.h $(INCDIR)/npc.h
$(OBJDIR)/npc.o: $(INCDIR)/npc.h $(INCDIR)/game.h
$(OBJDIR)/combat.o: $(INCDIR)/combat.h $(INCDIR)/player.h $(INCDIR)/npc.h
$(OBJDIR)/save.o: $(INCDIR)/save.h $(INCDIR)/game.h
$(OBJDIR)/time.o: $(INCDIR)/time.h $(INCDIR)/game.h $(INCDIR)/event.h
$(OBJDIR)/event.o: $(INCDIR)/event.h $(INCDIR)/game.h
$(OBJDIR)/services.o: $(INCDIR)/services.h $(INCDIR)/game.h