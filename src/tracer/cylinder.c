#include "../../miniRT.h"

static void		cylinder_contact(t_ray *ray, t_cylinder *cyl);
static double	distance(double t[2], double l[2], double product);
static void		swap(double v[2]);
static void		contact_data(double d, t_ray *ray, t_cylinder *cyl);

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
	double	f[3];
	double	delta;
	double	t[2];
	double	limits[2];

	vec_mc[0] = cyl->pos[0] - ray->pos[0];
	vec_mc[1] = cyl->pos[1] - ray->pos[1];
	vec_mc[2] = cyl->pos[2] - ray->pos[2];
	f[0] = 1 - 2 * pow(scalar_product(ray->vector, cyl->vector), 2);
	f[1] = 4 * scalar_product(ray->vector, cyl->vector) * scalar_product(vec_mc, cyl->vector);
	f[1] -= 2 * scalar_product(vec_mc, ray->vector);
	f[2] = scalar_product(vec_mc, vec_mc) - pow(cyl->diameter / 2, 2);
	f[2] -= 2 * pow(scalar_product(vec_mc, cyl->vector), 2);
	delta = pow(f[1], 2) - 4 * f[0] * f[2];
	if (delta >= 0)
	{
		t[0] = (-f[1] - sqrt(delta)) / (2 * f[0]);
		t[1] = (-f[1] + sqrt(delta)) / (2 * f[0]);
		limits[0] = -cyl->height / 2 + scalar_product(vec_mc, cyl->vector);
		limits[1] = +cyl->height / 2 + scalar_product(vec_mc, cyl->vector);
		contact_data(distance(t, limits, scalar_product(ray->vector, cyl->vector)),
			ray, cyl);
	}
}

static double	distance(double t[2], double l[2], double product)
{
	bool	in_r[2];

	if (t[1] <= t[0])
		swap(t);
	in_r[0] = (l[0] <= t[0] * product && t[0] * product <= l[1]);
	in_r[1] = (l[0] <= t[1] * product && t[1] * product <= l[1]);
	if (t[0] > 0 && in_r[0])
		return (t[0]);
	if (t[1] > 0 && in_r[1])
		return (t[1]);
	return (0);
}

static void	swap(double v[2])
{
	double	s;

	s = v[1];
	v[1] = v[0];
	v[0] = s;
}

static void	contact_data(double d, t_ray *ray, t_cylinder *cyl)
{
	if (d > 0 && d < ray->c_distance)
	{
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
