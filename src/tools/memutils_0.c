#include "../../miniRT.h"

void	*mrt_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((int)count < 0 && (int)size < 0)
		return (0);
	ptr = malloc(count * size);
	if (!ptr)
		return (0);
	mrt_memset(ptr, 0, count * size);
	return (ptr);
}


void	mrt_memset(void *p, int c, uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		*(unsigned char *)(p + i) = (unsigned char)c;
		i += 1;
	}
}

t_return	mrt_init(t_minirt *mrt)
{
//	mrt = mrt_calloc(1, sizeof(mrt));
//	if (!mrt)
//		return (R_MALLOC);

// brooh??
	mrt_memset(mrt, 0, sizeof(t_minirt)); // i guess it's enough
	return (R_SUCCESS);
}
