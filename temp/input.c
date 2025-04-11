//
// RUN COMMAND: gcc temp/input.c -o temp/run && ./temp/run
//
// TODO need to add a way to delete (show you delete)
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int getch(void) {
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

char *input() {
	static char buffer[1024]; // Buffer for manual input
	int buf_index = 0;
	while (1) {
		int ch = getch();

		if (ch == 27) { // Escape sequence
			ch = getch();
			if (ch == 91) {
				ch = getch();
				switch (ch) {
				case 65:
					printf("You pressed Up Arrow!\n");
					break;
				case 66:
					printf("You pressed Down Arrow!\n");
					break;
				case 67:
					printf("");
					fflush(stdout);
					break;
				case 68:
					if (buf_index >= 0) {
						buf_index--;
						printf("\b");
						fflush(stdout);
					}
					/* printf("You pressed Left Arrow!\n"); */
					break;
				default:
					printf("Unknown sequence: %d\n", ch);
					break;
				}
			}
			// Clear buffer if needed
			buf_index = 0;
			/* buffer[0] = '\0'; */
		} else if (ch == '\n') { // Enter key
			if (buf_index > 0) {
				buffer[buf_index] = '\0'; // Null-terminate
				printf("\nYou typed: %s\n", buffer);
				buf_index = 0; // Reset buffer
				return buffer;
			} else {
				printf("\n");
			}
		} else if (ch == 127) {
			if (buf_index > 0) {
				buf_index--;
				buffer[buf_index] = '\0';

				printf("\b \b");
				fflush(stdout);
			}
		} else {
			// Regular character, add to buffer
			// sizeof
			/* printf("") */
			if (buf_index < sizeof(buffer) - 1) {
				buffer[buf_index] = ch;
				buf_index++;
				putchar(ch); // Echo character to terminal
				fflush(stdout);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	while (1) {
		char *in = input();
		printf("%s\n", in);
	}
	return EXIT_SUCCESS;
}
