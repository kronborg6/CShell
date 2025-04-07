build:
	@gcc -Iinclude src/main.c src/helpers.c -o bin/main
run: build
	@./bin/main
