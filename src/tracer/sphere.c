#include "../../miniRT.h"

static void	sphere_contact(t_ray *ray, t_sphere *sphere);
static void	contact_data(double d, t_ray *ray, t_sphere *sphere);

void	check_sphere(t_ray *ray, t_sphere *sphere)
{
	while (sphere)
	{
		if (!ray->inside_obj)
			sphere_contact(ray, sphere);
		sphere = sphere->next;
	}
}

static void	sphere_contact(t_ray *ray, t_sphere *sphere)
{
	double	delta;
	double	t1;
	double	t2;
	double	vec_mc[3];

	vec_mc[0] = sphere->pos[0] - ray->pos[0];
	vec_mc[1] = sphere->pos[1] - ray->pos[1];
	vec_mc[2] = sphere->pos[2] - ray->pos[2];
	delta = 4 * pow(scalar_product(ray->vector, vec_mc), 2);
	delta -= 4 * (scalar_product(vec_mc, vec_mc) - pow(sphere->diameter / 2, 2));
	if (delta > 0) // think about case delta == 0
	{
		t1 = (2 * scalar_product(ray->vector, vec_mc) - sqrt(delta)) / 2;
		t2 = (2 * scalar_product(ray->vector, vec_mc) + sqrt(delta)) / 2;
		if (t2 > 0)
			contact_data(t1, ray, sphere);
	}
}

static void	contact_data(double d, t_ray *ray, t_sphere *sphere)
{
	double	dist_mc;

	if (d <= 0)
		ray->inside_obj = true;
	else if (d < ray->c_distance || ray->c_distance == 0)
	{
		ray->c_pos[0] = ray->pos[0] + d * ray->vector[0];
		ray->c_pos[1] = ray->pos[1] + d * ray->vector[1];
		ray->c_pos[2] = ray->pos[2] + d * ray->vector[2];
		ray->c_color[0] = sphere->color[0];
		ray->c_color[1] = sphere->color[1];
		ray->c_color[2] = sphere->color[2];
		ray->c_distance = d;
		ray->obj_type = SPHERE;
	}
}
