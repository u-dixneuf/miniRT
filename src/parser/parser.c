#include "../../miniRT.h"

t_return	mrt_parser(const char *filename, t_minirt *mrt)
{
	int			fd;
	t_return	ret;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (mrt_error(FILE_OPN), R_FILEDESC);
	ret = mrt_extract(fd, mrt);
	if (ret)
		return (close(fd), ret);
	return (close(fd), ret);
}
