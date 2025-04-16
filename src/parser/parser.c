#include "../../miniRT.h"

t_return	mrt_parser(const char *filename, t_minirt *mrt)
{
	char		fcontent;
	char 		**flines;
	t_return	ret;

	fcontent = mrt_readfile(filename);
	if (!fcontent)
		return (mrt_error(FILE_OPN), R_FILEDESC);
	flines = mrt_split(fcontent, '\n');
	mrt_free((void **)&fcontent);
	if (!flines)
		return (mrt_error(CNT_SPLT), R_CNTSPLT);
	while (*flines)
	{
		ret = mrt_extract(mrt, *flines);
		if (ret)
			return (mrt_free_arr(flines), ret);
		flines++;
	}
	return (mrt_free_arr(flines), R_SUCCESS);
}
