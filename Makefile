CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/input.c
OUT = build/vernam.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f build/$(TARGET)
