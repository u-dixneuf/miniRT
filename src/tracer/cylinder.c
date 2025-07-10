#include "../../miniRT.h"

static void		cylinder_contact(t_ray *ray, t_cylinder *cyl);

void	check_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	while (cylinder)
	{
		if (!ray->inside_obj)
			cylinder_contact(ray, cylinder);
		cylinder = cylinder->next;
	}
}

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl)
{
	double	vec_mc[3];

	vec_mc[0] = cyl->pos[0] - ray->pos[0];
	vec_mc[1] = cyl->pos[1] - ray->pos[1];
	vec_mc[2] = cyl->pos[2] - ray->pos[2];
	// check if inside cylinder
	// calculate lateral contact distance (-1 if no contact)
	// calculate base contact distance
	// compare distances and conclude if distance smaller than original dis
	double	lateral_distance;
	double	linear_distance;

	linear_distance = fabs(scalar_product(vec_mc, cyl->vector));
	lateral_distance = pow(vector_norme(vec_mc), 2) - pow(linear_distance, 2);
	lateral_distance = sqrt(lateral_distance);
	if (linear_distance <= cyl->height / 2
		&& lateral_distance <= cyl->diameter / 2)
		ray->inside_obj = true;
	else
	{
		
	}
}
