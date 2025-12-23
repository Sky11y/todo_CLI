#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1023

static char* fn_strchr(const char *str, char c)
{
	size_t i;

	if (!str) {
		return NULL;
	}

	for (i = 0; str[i];  ++i) {
		if (str[i] == c) {
			return (char *)&str[i];
		}
	}
	return NULL;
}

static char *fn_strjoin(char *dst, const char *src)
{
	char *new;
	size_t dst_len;
	size_t src_len;
	size_t i;

	if (!src) {
		return dst;
	}
	dst_len = dst ? strlen(dst) : 0;
	src_len = strlen(src);
	new = (char *)realloc(dst, sizeof(char) * (dst_len + src_len + 1));
	if (!new) {
		return NULL;
	}
	for (i = 0; src[i]; ++i) {
		new[dst_len + i] = src[i];
	}
	new[dst_len + i] = '\0';
	return (new);
}

static char *fn_finish_line(char *temp, char *buf, size_t n)
{
	size_t	i;
	char	*line;

	if (n == 0) {
		return NULL;
	}
	line = (char *)malloc(sizeof(char) * (n + 1));
	memcpy(line, temp, n);
	line[n] = '\0';

	++n;
	for (i = 0; temp[n + i]; ++i) {
		buf[i] = temp[n + i];
	}
	buf[i] = '\0';
	return line;
}

//char* fn_getline(int fd)
char *fn_getline(int fd)
{
	char		*line;
	char		*temp;
	char		*end_of_line;
	ssize_t		bytes_read;
	static char	buf[BUFFER_SIZE + 1];

	if (fd < 0) {
		return NULL;
	}

	temp = NULL;
	temp = fn_strjoin(temp, buf);
	while ((end_of_line = fn_strchr(temp, '\n')) == NULL) {
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 1) {
			free(temp);
			return NULL;
		}
		buf[bytes_read] = '\0';
		line = fn_strjoin(temp, buf);
		if (!line) {
			free(temp);
			return NULL;
		}
		temp = line;
		line = NULL;
	}
	line = fn_finish_line(temp, buf, end_of_line - temp);
	free(temp);
	if (line && line[0] == '\0') {
		free(line);
		line = NULL;
	}
	return line;
}
