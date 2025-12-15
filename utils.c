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


