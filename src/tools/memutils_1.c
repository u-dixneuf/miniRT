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

void free_link(void *obj)
{
	void	*next;

    if (obj)
    {
        while (obj)
        {
            next = *(void **)((char *)obj);
            mrt_free(&obj);
            obj = next;
        }
    }
}

void mrt_free_all(t_minirt *mrt)
{
    free_link((void *)mrt->sphere);
    free_link((void *)mrt->plane);
    free_link((void *)mrt->cylinder);
    mrt_freemlx(mrt->mlx);
}
