#include "../../miniRT.h"

void	mrt_free_arr(char **arr)
{
	uint64_t	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
		{
			mrt_free((void **)&arr[i]);
			arr[i] = NULL;
			i++;
		}
		mrt_free((void **)&arr);
		arr = NULL;
	}
}

void	mrt_free(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

void	mrt_free_all(t_minirt *mrt)
{
	mrt_free((void **)mrt->sphere);
	mrt_free((void **)mrt->plane);
	mrt_free((void **)mrt->cylinder);
	mrt_freemlx(mrt->mlx);
}
