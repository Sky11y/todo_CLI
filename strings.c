#include "todo.h"

void strtrim(char *restrict str, const char* restrict chars)
{
	uint i = 0;
	uint j = strlen(str);

	//empty string -> return
	if (i == j) {
		return ;
	}

	while (i < j && is_any_of(str[i], chars) == 1) {
		++i;
	}

	//contains only *chars*. Return empty string.
	if (i == j) {
		str[0] = '\0';
		return ;
	}

	while (j > i && is_any_of(str[j - 1], chars) == 1) {
		--j;
	}

	memmove(str, &str[i], j - i);
	str[j - i] = '\0';
}

void strtrim_front(char *restrict str, const char *restrict chars)
{
	uint i = 0;
	uint len;

	while (str[i] && is_any_of(str[i], chars) == 1) {
		++i;
	}

	if (str[i] == '\0') {
		str[0] = '\0';
		return ;
	}

	len = strlen(str) - i;
	memmove(str, &str[i], len);
	str[len] = '\0';
}

void strtrim_back(char *restrict str, const char *restrict chars)
{
	uint i = strlen(str);

	if (i == 0) {
		return ;
	}

	while (i > 0 && is_any_of(str[i - 1], chars) == 1) {
		--i;
	}

	str[i] = '\0';
}

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

void str_to_lower(char *restrict str)
{
	uint i;

	if (!str) {
		return ;
	}
	
	for (i = 0; str[i]; ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
}

void str_to_upper(char *restrict str)
{
	uint i;

	if (!str) {
		return ;
	}
	
	for (i = 0; str[i]; ++i) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
}
