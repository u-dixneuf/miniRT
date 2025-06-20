#include "../../miniRT.h"

static void	cylinder_contact(t_ray *ray, t_cylinder *cyl);

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

}
