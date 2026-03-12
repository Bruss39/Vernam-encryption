CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src/main.c src/input.c src/files.c src/vernam.c
OUT = build/vernam.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f build/$(TARGET)
