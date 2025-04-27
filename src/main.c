#include "cShell.h"
#include "commands.h"
#include "history.h"
#include "input.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

bool run = true;

int main() {
	if (init_system_path() != 0) {
		return 1;
	}
	initHistory(4);
	/* printf("%s\n", system_path); */
	while (run) {
		printf("%s>", system_path);
		char *in = input(system_path);
		if (in[0] != '\0') {
			Commands(in);
		}
	}
	deinitHistory();
	deinit_system_path();
	return 0;
}
