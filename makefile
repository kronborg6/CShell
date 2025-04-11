CC = gcc
CFLAGS = -Iinclude
SRC = $(wildcard src/*.c)
OUT = bin/main

all: build

bear:
	bear -- make build

build:
	@$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: build
	@./$(OUT)
