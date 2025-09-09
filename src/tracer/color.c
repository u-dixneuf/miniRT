#include "../../miniRT.h"

int	get_color(t_minirt *mrt, t_ray *cray, t_ray *lray)
{
	bool	same_contact_point;
	int		i;

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
	if (!same_contact_point)
	{
		// means the contact point is shadowed by another object
		// return mix of object color and ambient light
		return (0x010000); // return red for debugging purposes
	}
	// else need to check cases where ray contacts object on the same side
	// or not as the light ray (inside for sp and pl / side for the plane)
	// using scalar product sign to determine angles....
	return (0x001000); // returning green for debugging purposes
}
