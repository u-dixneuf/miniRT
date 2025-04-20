#include "../../miniRT.h"

static size_t	count_words(const char *s, char sep)
{
	int64_t	count;
	int32_t	flag;

	flag = 0;
	count = 0;
	while (*s)
	{
		if (*s != sep && !flag)
		{
			count++;
			flag = 1;
		}
		else if (*s == sep)
			flag = 0;
		s++;
	}
	return (count);
}

static char	*copy_word(const char *s, char c)
{
	int64_t	len;
	int64_t	i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)mrt_calloc(len + 1, 1);
	if (!word)
		return (0);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	return (word);
}

static bool	init_split(const char *s, char c, char ***split, uint64_t *word_count)
{
	*word_count = count_words(s, c) + 1;
	*split = (char **)mrt_calloc((*word_count + 1), sizeof(char *));
	if (!*split)
		return (false);
	return (true);
}

char	**mrt_split(char const *s, char c)
{
	uint64_t	word_count;
	uint64_t	i;
	char	**split;

	if (!s || !init_split(s, c, &split, &word_count))
		return (NULL);
	i = 0;
	while (i < word_count - 1)
	{ 
		while (*s == c)
			s++;
		split[i] = copy_word(s, c);
		if (!split[i])
			return (mrt_free_arr(split), NULL);
		s += mrt_strlen(split[i]);
		i++;
	}
	split[i] = 0;
	return (split);
}
