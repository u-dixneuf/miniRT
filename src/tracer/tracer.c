#include "../../miniRT.h"

static int	trace_ray(t_minirt *mrt, int h, int w);

t_return	mrt_tracer(t_minirt *mrt)
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
	get_camera_vectors(&mrt->camera);
	while (h < SIZE)
	{
		w = 0;
		while (w < SIZE)
		{
			p_addr = (int *)(m->img_addr + h * m->sl + w * (m->bpx / 8));
			*p_addr = mlx_get_color_value(m->mlx_ptr, trace_ray(mrt, h, w));
			w += 1;
		}
		h += 1;
	}
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->img_ptr, 0, 0);
	return (R_SUCCESS);
}

static int	trace_ray(t_minirt *mrt, int h, int w)
{
	t_ray	camera_ray;
	t_ray	light_ray;

	mrt_memset(&camera_ray, 0, sizeof(t_ray));
	mrt_memset(&light_ray, 0, sizeof(t_ray));
	camera_ray.h = h;
	camera_ray.w = w;
	get_cameragrid_vector(mrt->camera, &camera_ray); // get vector going from camera to ray pixel
	get_closest_contact(mrt, &camera_ray);
	if (camera_ray.obj_type) // if ray intersects with an object
	{
		get_lightcontact_vector(mrt->light, &camera_ray, &light_ray);
		get_closest_contact(mrt, &light_ray);
		return (get_color(mrt, &camera_ray, &light_ray));
	}
	return (0);
}
 