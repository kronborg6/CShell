#include "input.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
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
char *input() {
	static char buffer[1024];
	int buf_index = 0;
	int cursor_index = 0;

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
					break;
				case 66:
					break;
				}
			}
		} else if (ch == '\n') { // Enter key
			buffer[buf_index] = '\0';
			printf("\nYou typed: %s\n", buffer);
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
