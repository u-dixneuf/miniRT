#include "../../miniRT.h"

t_return	mrt_parser(const char *filename, t_minirt *mrt)
{
	char		*fcontent;
	char 		**flines;
	t_return	ret;
	int32_t		i;

	fcontent = mrt_readfile(filename);
	if (!fcontent)
		return (mrt_error(FILE_OPN), R_FILEDESC);
	flines = mrt_split(fcontent, '\n');
	mrt_free((void **)&fcontent);
	if (!flines)
		return (mrt_error(FCNT_SPLT), R_FCNTSPLT);
	i = 0;
	while (flines[i])
	{
		ret = mrt_extract(mrt, flines[i]);
		if (ret)
		{
			write(STDOUT_FILENO, "\t\\__LINE: ", 10);
			write(STDOUT_FILENO, flines[i], mrt_strlen(flines[i]));
			write(STDOUT_FILENO, "\n", 1);
			return (mrt_free_arr(flines), ret);
		}
		i++;
	}
	return (mrt_free_arr(flines), R_SUCCESS);
}
