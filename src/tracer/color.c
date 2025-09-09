#include "../../miniRT.h"

int	get_color(t_minirt *mrt, t_ray *cray, t_ray *lray)
{
	bool		same_contact_point;
	int8_t		i;
	uint32_t	*contact_color;
	double		final_color;

	same_contact_point = true;
	i = 0;
	while (i < 3 && same_contact_point)
	{
		if (lray->c_pos[i] != cray->c_pos[i])
			same_contact_point = false;
		i += 1;
	}
	// im not checking if the contact point is at the same object
	// since objects cannot physically be at the same point in space
	// will check if i need to add something when testing
	if (cray->obj_type == PLANE)
		contact_color = ((t_plane *)(cray->obj_ptr))->color;
	else if (cray->obj_type == SPHERE)
		contact_color = ((t_sphere *)(cray->obj_ptr))->color;
	else
		contact_color = ((t_plane *)(cray->obj_ptr))->color;
	if (!same_contact_point)
	{
		// means the contact point is shadowed by another object
		// return mix of object color and ambient light
		final_color = (contact_color[0] + mrt->ambient.ratio * mrt->ambient.color[0]) * 0x100000;
		final_color += (contact_color[1] + mrt->ambient.ratio * mrt->ambient.color[1]) * 0x1000;
		final_color += (contact_color[2] + mrt->ambient.ratio * mrt->ambient.color[2]) * 0x10;
		return ((int)final_color);
	}
	// else need to check cases where ray contacts object on the same side
	// or not as the light ray (inside for sp and pl / side for the plane)
	// using scalar product sign to determine angles....
	final_color = contact_color[0] * mrt->light.ratio * 0x100000;
	final_color += contact_color[1] * mrt->light.ratio * 0x1000;
	final_color += contact_color[2] * mrt->light.ratio * 0x10;
	return ((int)final_color); // returning green for debugging purposes
}
