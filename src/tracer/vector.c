#include "../../miniRT.h"

void	get_first_vector(t_camera camera, t_ray *ray)
{
	// calculate ray vector in standard coordinates
	double	pixel_size;
	double	w_factor;
	double	h_factor;
	double	fov_rad;
	uint8_t	i;

	fov_rad = (camera.fov * acos(-1)) / 180;
	pixel_size = 2 * tan(fov_rad / 2) / SIZE;
	w_factor = ray->w - (SIZE / 2);
	h_factor = ray->h - (SIZE / 2);
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
	/* debug */
	// printf("ray[%d][%d], vector [%lf][%lf][%lf]\n", ray->h, ray->w, ray->vector[0], ray->vector[1], ray->vector[2]);
	/* debug */
}

// void		get_second_vector(t_light light, ?);