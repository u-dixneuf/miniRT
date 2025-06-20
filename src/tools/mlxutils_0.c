#include "../../miniRT.h"

t_return	mrt_initmlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (mrt_error(MLX_INIT), R_LIBMLX);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SIZE, SIZE, "miniRT");
	if (!mlx->win_ptr)
		return (mrt_error(WIN_INIT), R_LIBMLX);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SIZE, SIZE);
	if (!mlx->img_ptr)
		return (mrt_error(IMG_INIT), R_LIBMLX);
	return (R_SUCCESS);
}

void	mrt_freemlx(t_mlx mlx)
{
	(void)mlx; // todo
}
