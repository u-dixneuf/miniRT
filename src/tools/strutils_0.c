#include "../../miniRT.h"

void	mrt_error(const char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, error_msg, mrt_strlen(error_msg));
}

bool	mrt_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return (true);
		s++;
	}
	return (false);
}

bool	mrt_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

uint32_t	mrt_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s + len))
		len++;
	return (len);
}

uint64_t	mrt_strlcpy(char *dst, const char *src, uint64_t dstsize)
{
	uint64_t	i;
	uint64_t	src_len;
	char		*s;

	i = 0;
	s = (char *)src;
	src_len = mrt_strlen(src);
	while (dstsize != 0 && i < dstsize - 1 && *(s + i))
	{
		*(dst + i) = *(s + i);
		i++;
	}
	if (dstsize != 0)
		*(dst + i) = '\0';
	return (src_len);
}