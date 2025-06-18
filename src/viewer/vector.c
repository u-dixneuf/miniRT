#include "../../miniRT.h"

void	get_first_vector(t_camera camera, t_ray *ray)
{
	// calculate ray vector in standard coordinates
	double	pixel_size;
	double	w_factor;
	double	h_factor;
	uint8_t	i;

	pixel_size = 2 * tan((double)camera.fov / 2) / SIZE;
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
}

void	set_vector(double vector[3], double x, double y, double z)
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
}
