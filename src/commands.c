#include "commands.h"
#include "cShell.h"
#include "helpers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Commands(char *command) {

	char **tokens;
	tokens = splitString(command, ' ');

	for (size_t i = 0; tokens[i]; i++) {
		tokens[i][strcspn(tokens[i], "\n")] = 0;
	}

	if (strcmp(tokens[0], "exit") == 0) {
		printf("sorry to se you go\n");
		run = false;
	} else if (strcmp(tokens[0], "echo") == 0) {
		for (int i = 1; tokens[i]; i++) {
			printf("%s", tokens[i]);
			printf(" ");
		}
		printf("\n");
		/* printf("%s\n", tokens[1]); */
	} else {
		printf("cShell: 404\ncommand: %s\n", command);
	}
	free(tokens);
}
