#include "../../miniRT.h"

void	get_color(t_ray *ray, t_minirt *mrt)
{
	t_ray	b_ray;

	if (ray->obj_type == 0 || ray->inside_obj)
	{	
		ray->color = 0;
		return ;
	}
	else
		ray->color = ray->c_color[0] * 0x010000 + ray->c_color[1] * 0x0100 + ray->c_color[2] * 0x01;
	mrt_memset(&b_ray, 0, sizeof(t_ray));
	// b_ray.pos[0] = ray->c_pos[0];
	// b_ray.pos[1] = ray->c_pos[1];
	// b_ray.pos[2] = ray->c_pos[3];
	// b_ray.vector[0] = mrt->light.pos[0] - b_ray.pos[0];
	// b_ray.vector[1] = mrt->light.pos[1] - b_ray.pos[1];
	// b_ray.vector[2] = mrt->light.pos[2] - b_ray.pos[2];
	// normalize_vector(b_ray.vector);
	// check_plane(&b_ray, mrt->n_plane, mrt->plane);
	// check_sphere(&b_ray, mrt->n_sphere, mrt->sphere);
	// check_cylinder(&b_ray, mrt->n_cylinder, mrt->cylinder);
	// if (b_ray.obj_type)
	// 	ray->color = mrt->ambient.color[0] * 0x010000 + mrt->ambient.color[1] * 0x0100
	// 		+ mrt->ambient.color[2] * 0x01;
	// else
	// 	ray->color = 0;
	/* debug */
	// printf("ray [%d][%d], inside %d, contact %d, distance %lf\n", ray->w, ray->h,
	// 		ray->inside_obj, ray->obj_type, ray->c_distance);
	/* debug */
}
