CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCS = main.c game.c player.c world.c npc.c combat.c save.c time.c event.c services.c
OBJS = $(SRCS:.c=.o)
TARGET = two_pieces

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -DDEBUG
debug: all

# Fix for tab issues in makefiles
.RECIPEPREFIX = $(TAB)