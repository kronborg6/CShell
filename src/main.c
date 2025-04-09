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

void Commands(char *command) {

	char **tokens;
	tokens = splitString(command, ' ');

	for (size_t i = 0; tokens[i]; i++) {
		tokens[i][strcspn(tokens[i], "\n")] = 0;
	}

	if (strcmp(tokens[0], "exit") == 0) {
		printf("sorry to se you go\n");
		run = false;
	}
	if (strcmp(tokens[0], "echo") == 0) {
		printf("hello\n");
	}
	free(tokens);
}
int main() {
	char *str = NULL;
	size_t len = 0;
	ssize_t read;
	while (run) {
		printf("> ");
		read = getline(&str, &len, stdin);
		if (read != -1) {
			Commands(str);
		}
	}
	return 0;
}
