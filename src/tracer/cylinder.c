#include "../../miniRT.h"

static void		cylinder_contact(t_ray *ray, t_cylinder *cyl);

void	check_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	while (cylinder)
	{
		cylinder_contact(ray, cylinder);
		cylinder = cylinder->next;
	}
}

// static double	get_lateral(t_ray *ray, t_cylinder *cyl, double	vec_mc[3])
// {
// 	double	a;
// 	double	b;
// 	double	p[3]; // p[0].t^2 + p[1].t + p[2] = 0

// 	a = scalar_product(ray->vector, cyl->vector);
// 	b = scalar_product(vec_mc, cyl->vector);
// 	p[0] = pow(a * b, 2) - 2 * pow(a, 2) + 1;
// 	p[1] = -2 * (a * b + scalar_product(vec_mc, ray->vector));
// 	p[2] = scalar_product(vec_mc, vec_mc) - 2 * pow(b, 2) - pow(cyl->diameter / 2, 2);
// 	if (quadratic(p) && p[0] >= 0)
// 		return (p[0]);
// 	return (-1);
// }

// static double 	get_linear(t_ray *ray, t_cylinder *cyl, double	vec_mc[3])
// {

// }

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl)
{
	(void)ray;
	(void)cyl;
	// double	vec_mc[3];
	

	// normalize_vector(cyl->vector); // remove when parser checks for normalization
	// vec_mc[0] = cyl->pos[0] - ray->pos[0];
	// vec_mc[1] = cyl->pos[1] - ray->pos[1];
	// vec_mc[2] = cyl->pos[2] - ray->pos[2];

	// double	lateral_cdis;
	// //double	linear_cdis;
	// lateral_cdis = get_lateral(ray, cyl, vec_mc);
	// //linear_cdis = get_linear(ray, cyl, vec_mc);
	// //	compare them and conclude
	// printf("lateral contact distance is %lf\n", lateral_cdis);
	// if (lateral_cdis != -1 && (lateral_cdis < ray->c_distance || !ray->c_distance))
	// {
	// 	double d = lateral_cdis;
	// 	ray->c_pos[0] = ray->pos[0] + d * ray->vector[0];
	// 	ray->c_pos[1] = ray->pos[1] + d * ray->vector[1];
	// 	ray->c_pos[2] = ray->pos[2] + d * ray->vector[2];
	// 	ray->c_color[0] = cyl->color[0];
	// 	ray->c_color[1] = cyl->color[1];
	// 	ray->c_color[2] = cyl->color[2];
	// 	ray->c_distance = d;
	// 	ray->obj_type = CYLINDER;
	// }
}
