#include "../../miniRT.h"

static char	*readfile_join(const char *s1, const char *s2)
{
	size_t	total_len;
	char	*res;

	if (!s1)
		return (mrt_strdup(s2));
	if (!s2)
		return (mrt_strdup(s1));
	total_len = mrt_strlen(s1) + mrt_strlen(s2);
	res = (char *)mrt_calloc(1, sizeof(char) * (total_len + 1));
	if (res == NULL)
		return (NULL);
	mrt_strlcpy(res, s1, mrt_strlen(s1) + 1);
	mrt_strlcat(res, s2, total_len + 1);
	return (res);
}

static bool	check_ext(const char *filename)
{
	char	*ext;

	ext = mrt_strrchr(filename, '.');
	if (!ext || mrt_strcmp(ext, ".rt"))
		return (false);
	return (true);
}

char	*mrt_readfile(const char *filename)
{
	int32_t	fd;
	int32_t	rbytes;
	char	buffer[FREAD_SIZE + 1];
	char	*data;
	char	*p;

	if (!check_ext(filename))
		return (mrt_error(INVL_EXT), NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	rbytes = FREAD_SIZE;
	data = NULL;
	while (rbytes >= FREAD_SIZE)
	{
		rbytes = read(fd, &buffer, FREAD_SIZE);
		buffer[rbytes] = 0;
		p = data;	
		data = readfile_join(data, buffer);
		if (p)
			mrt_free((void **)&p);
	}
	close(fd);
	return (data);
}
