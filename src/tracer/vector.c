#include "../../miniRT.h"

void	get_camera_vectors(t_camera *camera)
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

static void	fisheye_fix(double *ps,  double fov_rad, double wf, double hf)
{
	if (wf > 0)
		ps[0] = tan(fov_rad * wf / (SIZE - 1));
	else
		ps[0] = -tan(fov_rad * -wf / (SIZE - 1));
	if (hf > 0)
		ps[1] = tan(fov_rad * hf / (SIZE - 1));
	else
		ps[1] = -tan(fov_rad * -hf / (SIZE - 1));
	printf("wf [%lf] hf [%lf] ws [%lf] hs [%lf]\n\n", wf, hf, ps[0], ps[1]);
}

void	get_cameragrid_vector(t_camera camera, t_ray *ray) /// fish-eye motherfucker
{
	double	pixel_size[2]; // [w,h]
	double	fov_rad;
	double	w_factor;
	double	h_factor;
	uint8_t	i;

	fov_rad = (camera.fov * acos(-1)) / 180;
	w_factor = (ray->w - (SIZE / 2));
	h_factor = (ray->h - (SIZE / 2));
	fisheye_fix(pixel_size, fov_rad, w_factor, h_factor);
	i = 0;
	while (i < 3)
	{
		ray->pos[i] = camera.pos[i];
		ray->vector[i] = camera.vector[i];
		ray->vector[i] += pixel_size[0] * camera.w_vector[i];
		ray->vector[i] += pixel_size[1] * camera.h_vector[i];
		i += 1;
	}
	normalize_vector(ray->vector);
}

void	get_lightcontact_vector(t_light light, t_ray *cray, t_ray *lray)
{
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		lray->pos[i] = light.pos[i];
		lray->vector[i] = cray->c_pos[i] - light.pos[i];
		i += 1;
	}
	normalize_vector(lray->vector);
}

void	get_closest_contact(t_minirt *mrt, t_ray *ray)
{
	check_plane(ray, mrt->plane);
	check_sphere(ray, mrt->sphere);
	check_cylinder(ray, mrt->cylinder);
}
