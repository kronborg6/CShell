#include "helpers.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **splitStringOLD(char *a_str, const char a_delim) {

	char **result = 0;
	size_t count = 0;
	char *tmp = a_str;
	char *last_comma = 0;
	char delim[2];
	delim[0] = a_delim;
	delim[1] = 0;

	/* Count how many elements will be extracted. */
	while (*tmp) {
		if (a_delim == *tmp) {
			count++;
			last_comma = tmp;
		}
		tmp++;
	}

	/* Add space for trailing token. */
	count += last_comma < (a_str + strlen(a_str) - 1);

	/* Add space for terminating null string so caller
	   knows where the list of returned strings ends. */
	count++;

	result = malloc(sizeof(char *) * count);

	if (result) {
		size_t idx = 0;
		char *token = strtok(a_str, delim);

		while (token) {
			assert(idx < count);
			*(result + idx++) = strdup(token);
			token = strtok(0, delim);
		}
		assert(idx == count - 1);
		*(result + idx) = 0;
	}

	return result;
}
char **splitString(char *a_str, const char a_delim) {
	char **result = NULL;
	size_t count = 0;
	bool in_token = false;
	char delim[2] = {a_delim, '\0'};

	/* First pass: count how many tokens strtok will return */
	for (char *p = a_str; *p; ++p) {
		if (*p != a_delim) {
			if (!in_token) {
				in_token = true;
				++count;
			}
		} else {
			in_token = false;
		}
	}

	/* Allocate pointers: count tokens + 1 for the NULL terminator */
	result = malloc((count + 1) * sizeof *result);
	if (!result)
		return NULL;

	/* Second pass: actually split and strdup each token */
	size_t idx = 0;
	char *token = strtok(a_str, delim);
	while (token) {
		assert(idx < count);
		result[idx++] = strdup(token);
		token = strtok(NULL, delim);
	}
	assert(idx == count);

	/* NULL-terminate the array */
	result[idx] = NULL;
	return result;
}
