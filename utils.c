#include "todo.h"

uint safe_strlcpy(char *restrict dst, const char *restrict src, uint dsize)
{
	uint src_len = 0;
	uint i;

	while (src[src_len] && src_len < dsize - 1) {
		++src_len;
	}

	for (i = 0; i < src_len; ++i) {
		dst[i] = src[i];
	}

	dst[src_len] = '\0';
	return src_len;
}

int contains(const char *restrict test, const char *restrict chars)
{
	uint i;

	if (test == NULL) {
		return -1;
	}

	if (chars == NULL) {
		return 1;
	}

	for (i = 0; test[i]; ++i) {
		if (is_any_of(test[i], chars) == 1) {
				return 1;
		}
	}
	return 0;
}

int is_any_of(const char test, const char *restrict chars)
{ 
	uint i;

	if (test == '\0') {
		return -1;
	}

	if (chars == NULL) {
		return 1;
	}

	for (i = 0; chars[i]; ++i) {
		if (test == chars[i]) {
			return 1;
		}
	}
	return 0;
}

int is_all_of(const char *restrict test, const char *restrict chars)
{
	uint i;
	
	if (!test) {
		return -1;
	}

	if (!chars) {
		return 1;
	}

	for (i = 0; test[i]; ++i) {
		if (is_any_of(test[i], chars) == 0) {
			return 0;
		}
	}
	return 1;
}

