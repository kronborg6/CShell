#include "history.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

char **history = NULL;
int maxleng = 0;
int historyLen = 0;
int max_history_item_len = 0;

void initHistory(int count) {
	maxleng = count;
	history = (char **)malloc(count * sizeof(char *));
	if (history == NULL) {
		fprintf(stderr, "failed to init history\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < count; i++) {
		history[i] = NULL;
	}
}

void deinitHistory() {
	for (int i = 0; i < historyLen; i++) {
		free(history[i]);
	}
	free(history);
	history = NULL;
}

void appendHistory(char *string) {
	size_t len;
	len = strlen(string);

	if (len == 0) {
		return;
	}

	if (historyLen > 0 && strcmp(string, history[historyLen - 1]) == 0) {
		return;
	}
	if (len > max_history_item_len) {
		max_history_item_len = len;
	}
	if (maxleng >= historyLen + 1) {

		history[historyLen] = strdup(string);
		historyLen++;
	} else {
		int addSize = 10;
		history = (char **)realloc(history, (maxleng + addSize) * sizeof(char *));
		for (int i = maxleng + 1; maxleng + addSize > i; i++) {
			history[i] = NULL;
		}
		history[maxleng] = strdup(string);
		historyLen++;
		maxleng += addSize;
	}
}
