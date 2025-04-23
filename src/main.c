#include "cShell.h"
#include "commands.h"
#include "history.h"
#include "input.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool run = true;

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
