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
		printf("hello\n");
	}
	free(tokens);
}
int main() {
	/* size_t len; */
	/* char *old = NULL; */
	/* char old[1024]; */
	initHistory(10);
	while (run) {
		printf(">");
		char *in = input();
		/* len = sizeof(in); */
		/* memcpy(old, in, len); */
		/* old[len - 1] = '\0'; */
		/* char *in2 = input(); */
		/* printf("1: %s 2: %s\n", old, in2); */
		Commands(in);
	}
	freeHisoryKronborg();
	printf("freed\n");
	return 0;
}
