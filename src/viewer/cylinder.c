#include "../../miniRT.h"

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl);
static void	contact_data(double distance, t_ray *ray, t_cylinder *cyl, bool inside);

void	check_cylinder(t_ray *ray, uint32_t n, t_cylinder *cylinder)
{
	uint32_t	c;

	c = 0;
	while (c < n)
	{
		if (!ray->inside_obj)
			cylinder_contact(ray, cylinder);
		cylinder = cylinder->next;
		c += 1;
	}
}

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl)
{
	double	vec_mc[3];
	double	t1;
	double	t2;
	double	factor;
	double	distance;

	vec_mc[0] = cyl->pos[0] - ray->pos[0];
	vec_mc[1] = cyl->pos[1] - ray->pos[1];
	vec_mc[2] = cyl->pos[2] - ray->pos[2];
	factor = scalar_product(ray->vector, cyl->vector);
	t1 = -cyl->height / 2 + scalar_product(vec_mc, cyl->vector) / factor;
	t2 = cyl->height / 2 + scalar_product(vec_mc, cyl->vector) / factor;
	if (t1 >= 0 || t2 >= 0)
	{
		if ((t1 < 0 && t2 >= 0) || (t1 >= 0 && t2 >= 0 && t2 <= t1))
			distance = t2;
		else if ((t2 < 0 && t1 >= 0) || (t1 >= 0 && t2 >= 0 && t1 <= t2))
			distance = t1;
		contact_data(distance, ray, cyl, t1 * t2 <= 0);
	}
}

static void	contact_data(double d, t_ray *ray, t_cylinder *cyl, bool inside)
{
	if (d < ray->c_distance)
	{
		ray->c_pos[0] = ray->pos[0] + d * ray->vector[0];
		ray->c_pos[1] = ray->pos[1] + d * ray->vector[1];
		ray->c_pos[2] = ray->pos[2] + d * ray->vector[2];
		ray->c_color[0] = cyl->color[0];
		ray->c_color[1] = cyl->color[1];
		ray->c_color[2] = cyl->color[2];
		ray->c_distance = d;
		ray->inside_obj = inside;
		ray->obj_type = CYLINDER;
	}
}
