#include "../../miniRT.h"

void	mrt_memset(void *p, int c, u_int32_t size)
{
	u_int32_t	i;

	i = 0;
	while (i < size)
	{
		*(unsigned char *)(p + i) = (unsigned char)c;
		i += 1;
	}
}

void	mrt_init(t_minirt *mrt)
{
	mrt_memset(mrt, 0, sizeof(t_minirt)); // i guess it's enough
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
