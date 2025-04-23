#include "input.h"
#include "history.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

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

int get_terminal_width() {
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return w.ws_col;
}

/* static void redraw(const char *buffer, int length, int index) { */
/* 	int ter_max_leng = get_terminal_width(); */
/* 	int start = 1; */
/* 	int col = 0; */

/* 	// Go to line start */
/* 	printf("\r"); */
/* 	printf(">"); */
/* 	// Print buffer */
/* 	fwrite(buffer, 1, length, stdout); */
/* 	// Clear to end of line (optional) */
/* 	printf("\033[K"); */
/* 	// Move cursor back to the right position */
/* 	for (int i = length; i > index; i--) { */
/* 		printf("\b"); */
/* 	} */
/* 	fflush(stdout); */
/* } */

static void redraw(const char *buffer, int length, int index) {
	int ter_max_leng = get_terminal_width();
	int start = 1;
	int col = 0;

	// Go to line start
	printf("\033[?25l"); // hide cursor while redrawing
	printf("\033[0J");
	printf("\r");
	if (col == 0) {
		printf(">");
	}
	if (length > 10) {
		col++;
		printf("\n");
	}
	printf("\033[K");
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
						int foo = strlen(history[historyLen - hisory_index - 1]);
						for (int i = 0; i < strlen(history[historyLen - hisory_index - 1]); i++) {

							buffer[i] = history[historyLen - hisory_index - 1][i];
						}
						buf_index = foo;
						cursor_index = foo;
						redraw(buffer, buf_index, cursor_index);
						hisory_index++;
					}
					break;
				case 66: // som bug here
					if (hisory_index - 1 <= 0) {
						for (int i = 0; i < max_history_item_len; i++) {
							buffer[i] = '\0';
						}
						buf_index = 0;
						cursor_index = 0;
						redraw(buffer, buf_index, cursor_index);
						hisory_index = 0;
						break;
					} else if (hisory_index > 0) {

						/* int temp = hisory_index - 1; */
						int foo = strlen(history[historyLen - hisory_index + 1]);
						for (int i = 0; i < strlen(history[historyLen - hisory_index + 1]); i++) {

							buffer[i] = history[historyLen - hisory_index + 1][i];
						}
						for (int i = foo; i < 1024; i++) {
							buffer[i] = '\0';
						}
						buf_index = foo;
						cursor_index = foo;
						redraw(buffer, buf_index, cursor_index);
						hisory_index--;
					}
					break;
				}
			}
		} else if (ch == '\n') { // Enter key
			buffer[buf_index] = '\0';
			printf("\n");
			/* printf("\nYou typed: %s\n", buffer); */
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
