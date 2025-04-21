#include "helpers.h"
#include "input.h"
#include <stdbool.h>
#include <stddef.h>
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
		for (int i = 1; tokens[i]; i++) {
			printf("%s", tokens[i]);
			printf(" ");
		}
		printf("\n");
		/* printf("%s\n", tokens[1]); */
	}
	free(tokens);
}
int main() {
	initHistory(4);
	while (run) {
		printf(">");
		char *in = input();
		if (in[0] != '\0') {
			Commands(in);
		}
	}
	deinitHistory();
	return 0;
}
