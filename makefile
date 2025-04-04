build:
	@gcc -I../include src/main.c -o bin/main
run: build
	@./bin/main
