#include "../../miniRT.h"

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl);
static void	contact_data(double d, t_ray *ray, t_cylinder *cyl);

void	check_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	while (cylinder)
	{
		normalize_vector(cylinder->vector); // because parsing doenst check norme
		printf("norme of vector %lf\n", vector_norme(cylinder->vector));
		cylinder_contact(ray, cylinder);
		cylinder = cylinder->next;
	}
}

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl)
{
	// a.t^2 + b^t + c = 0
	double	p[3];
	double	vec_mc[3];
	double	t;
	double	d;

	vec_mc[0] = cyl->pos[0] - ray->pos[0];
	vec_mc[1] = cyl->pos[1] - ray->pos[1];
	vec_mc[2] = cyl->pos[2] - ray->pos[2];
	p[0] = 1 - pow(scalar_product(ray->vector, cyl->vector), 2);
	p[1] = scalar_product(ray->vector, vec_mc);
	p[1] += scalar_product(ray->vector, cyl->vector) * scalar_product(vec_mc, cyl->vector);
	p[1] *= -2;
	p[2] = scalar_product(vec_mc, vec_mc) - pow(cyl->diameter / 2, 2);
	p[2] += pow(scalar_product(vec_mc, cyl->vector), 2);
	if (quadratic(p) && p[1] >= 0)
	{
		if (p[0] >= 0)
			t = p[0];
		else
			t = p[1];
		d = t * scalar_product(ray->vector, cyl->vector);
		d -= scalar_product(vec_mc, cyl->vector);
		if (fabs(d) <= cyl->height / 2)
			contact_data(t, ray, cyl);
	}
}

static void	contact_data(double d, t_ray *ray, t_cylinder *cyl)
{
	if (d <= ray->c_distance || ray->c_distance == 0)
	{
		ray->c_pos[0] = ray->pos[0] + d * ray->vector[0];
		ray->c_pos[1] = ray->pos[1] + d * ray->vector[1];
		ray->c_pos[2] = ray->pos[2] + d * ray->vector[2];
		ray->c_distance = d;
		ray->obj_type = CYLINDER;
		ray->obj_ptr = (void *)cyl;
	}
}
