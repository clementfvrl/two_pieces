CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJ = main.o game.o player.o world.o npc.o combat.o save.o time.o event.o
TARGET = one_piece

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)