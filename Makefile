CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -lbcrypt

SRC = src/main.c src/input.c src/files.c src/vernam.c
OUT = build/vernam.exe

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f build/*
