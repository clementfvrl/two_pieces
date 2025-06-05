CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRCS = main.c game.c player.c world.c npc.c combat.c save.c time.c event.c services.c boss.c
OBJS = $(SRCS:.c=.o)
TARGET = one_piece

.PHONY: all clean run debug

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe 2>nul || exit 0

run: $(TARGET)
	./$(TARGET)

debug: CFLAGS += -DDEBUG
debug: all

.RECIPEPREFIX = $(TAB)
