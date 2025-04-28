#include "commands.h"
#include "cShell.h"
#include "cd.h"
#include "helpers.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void Commands(char *command) {
	char **tokens;
	tokens = splitString(command, ' ');

	for (size_t i = 0; tokens[i]; i++) {
		tokens[i][strcspn(tokens[i], "\n")] = 0;
	}

	int id = fork();

	if (id == 0) {
		if (strcmp(tokens[0], "exit") == 0) {
			/* printf("sorry to se you go\n"); */
			run = false;
		} else if (strcmp(tokens[0], "echo") == 0) {
			for (int i = 1; tokens[i]; i++) {
				printf("%s", tokens[i]);
				printf(" ");
			}
			printf("\n");
			/* printf("%s\n", tokens[1]); */
		} else {
			/* printf("cShell: 404\ncommand: %s\n", command); */
		}
		free(tokens);
		exit(EXIT_SUCCESS);
	} else if (id < 0) {
		printf("failed to fork");
	} else if (id > 0) {
		wait(NULL);
		if (strcmp(tokens[0], "exit") == 0) {
			printf("sorry to se you go\n");
			run = false;
		} else if (strcmp(tokens[0], "cd") == 0) {
			change_system_path(tokens[1]);
		} else if (strcmp(tokens[0], "pwd") == 0) {
			printf("%s\n", system_path);
		}
	}
}
