#include "../miniRT.h"

int	main(int ac, char **av)
{
	t_minirt	mrt;
	t_return	ret;

	if (ac != 2)
		return (mrt_error(ARGS_NUM), R_INVALID);
	mrt_init(&mrt);
	ret = mrt_parser(av[1], &mrt);
	if (ret)
		return (mrt_free_all(&mrt), ret);
	ret = mrt_initmlx(&mrt.mlx);
	if (ret)
		return (mrt_free_all(&mrt), ret);
	ret = mrt_tracer(&mrt);
	if (ret)
		return (mrt_free_all(&mrt), ret);
	/* debug */
	mlx_loop(mrt.mlx.mlx_ptr);
	/* debug */
	return (mrt_free_all(&mrt), R_SUCCESS);
}
