#include "history.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

char **history = NULL;
int maxleng = 0;
int historyLen = 0;
int max_history_item_len = 0;

struct HistoryData {
	char *command;
	size_t len;
	char time[30];
};

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
		appandfile(string, len);
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

void createFileIfNotExist() {
	FILE *fp = fopen("./.temp", "rb+");
	if (!fp) {
		fp = fopen("./.temp", "wb");
		if (!fp) {
			perror("opening .temp for creation");
			return;
		}
	}
	fclose(fp);
}
// read command in to history
void loadHistoryFromFile() {
	FILE *fp = fopen("./.temp", "rb+");
	fclose(fp);
}

// FORMAT ^SS:mm:HH:DD:MM:YYYY;LEN;COMMAND^
void appandfile(const char *command, size_t len) {
	FILE *fp = fopen("./.temp", "ab+");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(fp, "\n^%d:%02d:%02d:%02d:%02d:%02d;%zu;%s^", tm.tm_sec, tm.tm_min, tm.tm_hour, tm.tm_mday, tm.tm_mon + 1,
	        tm.tm_year + 1900, len, command);
	fclose(fp);
}
