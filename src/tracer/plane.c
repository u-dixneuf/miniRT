#include "../../miniRT.h"

static void	plane_contact(t_ray *ray, t_plane *plane);
static void	contact_data(double d,t_ray *ray, t_plane *plane);

void	check_plane(t_ray *ray, t_plane *plane)
{
	while (plane)
	{
		plane_contact(ray, plane);
		plane = plane->next;
	}
}

static void	plane_contact(t_ray *ray, t_plane *plane)
{
	double	dm;
	double	dn;
	double	v[3];
	double	n[3];

	v[0] = ray->pos[0] - plane->pos[0];
	v[1] = ray->pos[1] - plane->pos[1];
	v[2] = ray->pos[2] - plane->pos[2];
	dm = fabs(scalar_product(plane->vector, v));
	n[0] = ray->pos[0] + (dm / 2) * ray->vector[0];
	n[1] = ray->pos[1] + (dm / 2) * ray->vector[1];
	n[2] = ray->pos[2] + (dm / 2) * ray->vector[2];
	v[0] = n[0] - plane->pos[0];
	v[1] = n[1] - plane->pos[1];
	v[2] = n[2] - plane->pos[2];
	dn = fabs(scalar_product(plane->vector, v));
	if (dn < dm)
		contact_data(dm, ray, plane);
}

static void	contact_data(double d, t_ray *ray, t_plane *plane)
{
	double	contact_d;

	contact_d = d / fabs(scalar_product(plane->vector, ray->vector));
	if (contact_d <= ray->c_distance || ray->c_distance == 0)
	{
		ray->c_pos[0] = ray->pos[0] + contact_d * ray->vector[0];
		ray->c_pos[1] = ray->pos[1] + contact_d * ray->vector[1];
		ray->c_pos[2] = ray->pos[2] + contact_d * ray->vector[2];
		ray->c_color[0] = plane->color[0];
		ray->c_color[1] = plane->color[1];
		ray->c_color[2] = plane->color[2];
		ray->c_distance = contact_d;
		ray->obj_type = PLANE;
	}
}
