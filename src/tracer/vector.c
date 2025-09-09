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

void	get_cameragrid_vector(t_camera camera, t_ray *ray) /// fish-eye motherfucker
{
	double	pixel_size;
	double	w_factor;
	double	h_factor;
	double	fov_rad;
	uint8_t	i;

	fov_rad = (camera.fov * acos(-1)) / 180;
	pixel_size = 2 * tan(fov_rad / 2) / SIZE;
	w_factor = (ray->w - (SIZE / 2));
	h_factor = (ray->h - (SIZE / 2));
	i = 0;
	while (i < 3)
	{
		ray->pos[i] = camera.pos[i];
		ray->vector[i] = camera.vector[i];
		ray->vector[i] += w_factor * pixel_size * camera.w_vector[i];
		ray->vector[i] += h_factor * pixel_size * camera.h_vector[i];
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
	check_cylinder(ray, mrt->cylinder); //TODO
}
