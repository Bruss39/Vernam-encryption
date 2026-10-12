CC = gcc
CFLAGS = -std=c11 -Wall -Iinclude

ifeq ($(OS),Windows_NT)
LDFLAGS = -lbcrypt
OUT = build/vernam.exe
else
LDFLAGS =
OUT = build/vernam
endif

SRC = src/main.c src/input.c src/files.c src/vernam.c

.PHONY: all clean

all:
	mkdir -p build
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

clean:
	rm -f $(OUT)
