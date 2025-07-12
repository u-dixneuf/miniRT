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

static bool	quadratic(double p[3])
{
	double	delta;
	double	t[2];

	delta = pow(p[1], 2) - 4 * p[0] * p[2];
	if (delta >= 0)
	{
		t[0] = (-p[1] - sqrt(delta)) / (2 * p[0]);
		t[1] = (-p[1] + sqrt(delta)) / (2 * p[0]);
		if (fabs(t[0]) <= fabs(t[1]))
		{
			p[0] = t[0];
			p[1] = t[1];
		}
		else
		{
			p[0] = t[1];
			p[1] = t[0];
		}
		return (true);
	}
	return (false);
}

static double	get_lateral(t_ray *ray, t_cylinder *cyl, double	vec_mc[3])
{
	double	a;
	double	b;
	double	p[3]; // p[0].t^2 + p[1].t + p[2] = 0

	a = scalar_product(ray->vector, cyl->vector);
	b = scalar_product(vec_mc, cyl->vector);
	p[0] = pow(a * b, 2) - 2 * pow(a, 2) + 1;
	p[1] = -2 * (a * b + scalar_product(vec_mc, ray->vector));
	p[2] = scalar_product(vec_mc, vec_mc) - 2 * pow(b, 2) - pow(cyl->diameter / 2, 2);
	if (quadratic(p) && p[0] >= 0)
		return (p[0]);
	return (-1);
}

// static double 	get_linear(t_ray *ray, t_cylinder *cyl, double	vec_mc[3])
// {

// }

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
	lateral_distance = scalar_product(vec_mc, vec_mc) - pow(linear_distance, 2);
	lateral_distance = sqrt(lateral_distance);
	if (linear_distance <= cyl->height / 2
		&& lateral_distance <= cyl->diameter / 2)
		ray->inside_obj = true;
	else
	{
		double	lateral_cdis;
		//double	linear_cdis;

		lateral_cdis = get_lateral(ray, cyl, vec_mc);
		//linear_cdis = get_linear(ray, cyl, vec_mc);
		//	compare them and conclude
		if (lateral_cdis < ray->c_distance)
		{
			double d = lateral_cdis;
			ray->c_pos[0] = ray->pos[0] + d * ray->vector[0];
			ray->c_pos[1] = ray->pos[1] + d * ray->vector[1];
			ray->c_pos[2] = ray->pos[2] + d * ray->vector[2];
			ray->c_color[0] = cyl->color[0];
			ray->c_color[1] = cyl->color[1];
			ray->c_color[2] = cyl->color[2];
			ray->c_distance = d;
			ray->obj_type = CYLINDER;
		}
	}
}
