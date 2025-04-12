#include "helpers.h"
#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	while (run) {
		char *in = input();
		Commands(in);
	}
	return 0;
}
