#include "../../miniRT.h"

int32_t	mrt_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int32_t	mrt_strcmp(const char *s1, const char *s2)
{
	uint32_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i += 1;
	return (s1[i] - s2[i]);
}

char	*mrt_strdup(const char *s)
{
	char	*c;

	if (!s)
		return (NULL);
	c = (char *)malloc(sizeof(char) * (minishell_strlen(s) + 1));
	if (c == NULL)
		return (NULL);
	minishell_strlcpy(c, s, minishell_strlen(s) + 1);
	return (c);
}
