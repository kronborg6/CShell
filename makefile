CC = gcc
CFLAGS = -g -Iinclude -Wall
SRC = $(wildcard src/*.c)
OUT = bin/main

all: build

bear:
	bear -- make build

build:
	@$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: build
	@./$(OUT)
