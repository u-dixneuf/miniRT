#include "../../miniRT.h"

t_return	mrt_viewer(t_minirt *mrt)
{
	t_mlx	*m;
	int		p_color;
	int		*p_addr;
	int		h;
	int		w;

	m = &mrt->mlx;
	m->img_addr = mlx_get_data_addr(m->img_ptr, &m->bpx, &m->sl, &m->e);
	if (!m->img_addr)
		return (mrt_error(IMG_ADDR), R_LIBMLX);
	h = 0;
	while (h < HEIGHT)
	{
		w = 0;
		while (w < WIDTH)
		{
			p_addr = (int *)(m->img_addr + h * m->sl + w * (m->bpx / 8));
			*p_addr = mlx_get_color_value(m->mlx_ptr, mrt_trace(mrt, h, w));
			w += 1;
		}
		h += 1;
	}
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, 0, 0);
	return (R_SUCCESS);
}
