#include "../miniRT.h"

int	main(int ac, char **av)
{
	t_minirt	mrt;
	t_return	ret;

	if (ac != 2)
		return (mrt_error(ARGS_NUM), R_INVALID);
	if (mrt_init(&mrt))
		return (R_MALLOC);
	ret = mrt_parser(av[1], &mrt);
	if (ret)
		return (mrt_free_all(&mrt), ret);
	
	printf("success");
	// ret = mrt_initmlx(&mrt.mlx);
	// if (ret)
	// 	return (mrt_free_all(&mrt), ret);
	// ret = mrt_viewer(&mrt);
	// if (ret)
	// 	return (mrt_free_all(&mrt), ret);
	return (mrt_free_all(&mrt), R_SUCCESS);
}
