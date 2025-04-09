#include "helpers.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int mainOLD() {
	char loo[] = "Monday Tursday Wensday";
	char **tokens;
	char *str = NULL;
	size_t len = 0;
	ssize_t read;
	printf("hello\n");
	tokens = splitString(loo, ' ');
	read = getline(&str, &len, stdin);
	if (read != -1) {
		printf("typed: %s\n", str);
	}
	if (tokens) {
		int i;
		for (i = 0; *(tokens + i); i++) {
			printf("month=[%s]\n", *(tokens + i));
			free(*(tokens + i));
		}
		printf("\n");
		free(tokens);
	}
	int foo = 1;

	return 0;
}

bool run = true;

void Commands(char *command, int count, ...) {
	va_list args;
	va_start(args, count);

	command[strcspn(command, "\n")] = 0;

	if (strcmp(command, "exit") == 0) {
		printf("sorry to se you go\n");
		run = false;
	}
	if (strcmp(command, "echo") == 0) {
		printf("hello\n");
	}
}
int main() {
	char *str = NULL;
	size_t len = 0;
	ssize_t read;
	while (run) {
		printf("> ");
		read = getline(&str, &len, stdin);
		if (read != -1) {
			Commands(str, 0);
		}
	}
	return 0;
}
