#include "../../miniRT.h"

static void	get_camera_vectors(t_camera *camera);
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

static void	get_camera_vectors(t_camera *camera) // norm!!! ++ check if formulas are ok ++ didnt handle teta
{
	double	*T;
	double	*W;
	double	*H;
	double	f;

	T = camera->vector;
	W = camera->w_vector;
	H = camera->h_vector;
	if (fabs(T[0]) <= fabs(T[1]) && fabs(T[0]) <= fabs(T[2]))
	{
		f = sqrt(T[1] * T[1] + T[2] * T[2]);
		set_vector(W, 0, T[2] / f, -T[1] / f);
		set_vector(H, (T[1] * T[1] + T[2] * T[2]) / f, -T[0] * T[1] / f, -T[0] * T[2] / f);
	}
	else if (fabs(T[1]) <= fabs(T[0]) && fabs(T[1]) <= fabs(T[2]))
	{
		f = sqrt(T[0] * T[0] + T[2] * T[2]);
		set_vector(W, -T[2] / f, 0, T[0] / f);
		set_vector(H, (-T[0] * T[1]) / f, (T[0] * T[0] + T[2] * T[2]) / f, -T[1] * T[2] / f);
	}
	else if (fabs(T[2]) <= fabs(T[0]) && fabs(T[2]) <= fabs(T[1]))
	{
		f = sqrt(T[0] * T[0] + T[1] * T[1]);
		set_vector(W, T[1] / f, -T[0] / f, 0);
		set_vector(H, -T[0] * T[2] / f, -T[1] * T[2] / f, (T[0] * T[0] + T[1] * T[1]) / f);
	}
}

static int	trace_ray(t_minirt *mrt, int h, int w)
{
	t_ray	ray;

	mrt_memset(&ray, 0, sizeof(t_ray));
	ray.h = h;
	ray.w = w;
	get_first_vector(mrt->camera, &ray);
	check_plane(&ray, mrt->plane);
	check_sphere(&ray, mrt->sphere);
	check_cylinder(&ray, mrt->cylinder);
	get_color(&ray, mrt);
	return (ray.color);
}
