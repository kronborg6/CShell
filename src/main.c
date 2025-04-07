#include "helpers.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
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
