#include "input.h"
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

/* foo = (char **)malloc(5 * sizeof(char *)); */

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

void freeHisoryKronborg() {
	free(history);
	history = NULL;
}

static int getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}

static void redraw(const char *buffer, int length, int index) {
	// Go to line start
	printf("\r");
	printf(">");
	// Print buffer
	fwrite(buffer, 1, length, stdout);
	// Clear to end of line (optional)
	printf("\033[K");
	// Move cursor back to the right position
	for (int i = length; i > index; i--) {
		printf("\b");
	}
	fflush(stdout);
}

static void appendHistory(char *string) {
	size_t len;
	len = strlen(string);
	if (len > max_history_item_len) {
		max_history_item_len = len;
	}
	if (maxleng >= historyLen + 1) {

		history[historyLen] = (char *)malloc(len);
		memcpy(history[historyLen], string, len);
		historyLen++;
	} else {
		int addSize = 10;
		history = (char **)realloc(history, (maxleng + addSize) * sizeof(char *));
		for (int i = maxleng + 1; maxleng + addSize > i; i++) {
			history[i] = NULL;
		}
		history[maxleng] = (char *)malloc(len);
		memcpy(history[maxleng], string, len);
		historyLen++;
		maxleng += addSize;
	}
}
char *input() {
	static char buffer[1024];
	int buf_index = 0;
	int cursor_index = 0;
	int hisory_index = 0;

	while (1) {
		int ch = getch();

		if (ch == 27) { // Escape sequence
			ch = getch();
			if (ch == 91) {
				ch = getch();
				switch (ch) {
				case 67: // Right arrow
					if (cursor_index < buf_index) {
						cursor_index++;
						printf("\033[C"); // Move cursor right
						fflush(stdout);
					}
					break;
				case 68: // Left arrow
					if (cursor_index > 0) {
						cursor_index--;
						printf("\033[D"); // Move cursor left
						fflush(stdout);
					}
					break;
				case 65:
					if (hisory_index < historyLen) {
						int foo = strlen(history[hisory_index]);
						for (int i = 0; i < strlen(history[hisory_index]); i++) {

							buffer[i] = history[hisory_index][i];
						}
						/* buf_index = foo - 3; */
						/* cursor_index = foo - 3; */
						buf_index = foo;
						cursor_index = foo;
						redraw(buffer, buf_index, cursor_index);
					}
					hisory_index++;
					break;
				case 66:
					if (hisory_index > 0) {
						if (hisory_index - 1 <= 0) {
							for (int i = 0; i < max_history_item_len; i++) {
								buffer[i] = '\0';
							}
							buf_index = 0;
							cursor_index = 0;
							redraw(buffer, buf_index, cursor_index);
							hisory_index = 0;
							break;
						}
						int foo = strlen(history[hisory_index - 1]);
						for (int i = 0; i < strlen(history[hisory_index - 1]) - 1; i++) {

							buffer[i] = history[hisory_index - 1][i];
						}
						for (int i = foo + 1; i < 1024; i++) {
							buffer[i] = '\0';
						}
						/* buf_index = foo - 3; */
						/* cursor_index = foo - 3; */
						buf_index = foo;
						cursor_index = foo;
						redraw(buffer, buf_index, cursor_index);
					}
					hisory_index--;
					break;
				}
			}
		} else if (ch == '\n') { // Enter key
			buffer[buf_index] = '\0';
			printf("\nYou typed: %s\n", buffer);
			appendHistory(buffer);
			return buffer;
		} else if (ch == 127) { // Backspace
			if (cursor_index > 0) {
				for (int i = cursor_index - 1; i < buf_index - 1; i++) {
					buffer[i] = buffer[i + 1];
				}
				buf_index--;
				cursor_index--;
				redraw(buffer, buf_index, cursor_index);
			}
		} else { // Normal characters
			if (buf_index < sizeof(buffer) - 1) {
				for (int i = buf_index; i > cursor_index; i--) {
					buffer[i] = buffer[i - 1];
				}
				buffer[cursor_index] = ch;
				buf_index++;
				cursor_index++;
				redraw(buffer, buf_index, cursor_index);
			}
		}
	}
}
