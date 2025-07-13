#include "../../miniRT.h"

void	get_first_vector(t_camera camera, t_ray *ray)
{
	double	pixel_size;
	double	w_factor;
	double	h_factor;
	double	fov_rad;
	uint8_t	i;

	fov_rad = (camera.fov * acos(-1)) / (180 * 2);
	pixel_size = 2 * tan(fov_rad) / SIZE;
	fov_rad = fov_rad / SIZE; // angle to add in each pixel from center
	w_factor = (ray->w - (SIZE / 2)); // last factor is to fix the fish-eye effect  * (1 + cos(fov_rad * fabs(ray->w - (SIZE / 2))))
	h_factor = (ray->h - (SIZE / 2)); // turns out it just widens the fov like a real eye
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

// void		get_second_vector(t_light light, ?);