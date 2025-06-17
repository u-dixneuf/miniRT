#include "../../miniRT.h"

static int	mrt_trace(t_minirt *mrt, int h, int w);

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

static int	mrt_trace(t_minirt *mrt, int h, int w)
{
	t_ray	ray;

	mrt_memset(&ray, 0, sizeof(t_ray));
	get_vector(mrt->camera, &ray);
	check_sphere(mrt->n_sphere, mrt->sphere);
	check_plane(mrt->n_plane, mrt->plane);
	check_cylinder(mrt->n_cylinder, mrt->cylinder);
	get_color(&ray, mrt->ambient, mrt->light);
	return (ray.color);
}
