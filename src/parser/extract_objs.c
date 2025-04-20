#include "../../miniRT.h"


t_return	extract_sphere(t_minirt *mrt, char **info)
{
	t_sphere	*sphere;

	sphere = add_sphere(mrt);
	if (!sphere)
		return (R_MALLOC);
	if (!mrt_setcords(*info, sphere->pos))
		return (mrt_error(INVL_SPHERE_COORDINATES), R_INVALID);
	if (!mrt_setdouble(*(++info), &sphere->diameter))
		return (mrt_error(INVL_SPHERE_DIAMETER), R_INVALID);
	if (!mrt_setcolor(*(++info), sphere->color))
		return (mrt_error(INVL_SPHERE_COLOR), R_INVALID);
	if (*(++info))
		return (mrt_error(INVL_SPHERE_INFO), R_INVALID);
	return (R_SUCCESS);
}

t_return	extract_plane(t_minirt *mrt, char **info)
{
	t_plane	*plane;

	plane = add_plane(mrt);
	if (!plane)
		return (R_MALLOC);
	if (!mrt_setcords(*info, plane->pos))
		return (mrt_error(INVL_PLANE_COORDINATES), R_INVALID);
	if (!mrt_setvector(*(++info), plane->vector))
		return (mrt_error(INVL_PLANE_VECTOR), R_INVALID);
	if (!mrt_setcolor(*(++info), plane->color))
		return (mrt_error(INVL_PLANE_COLOR), R_INVALID);
	if (*(++info))
		return (mrt_error(INVL_PLANE_INFO), R_INVALID);
	return (R_SUCCESS);
}

t_return extract_cylinder(t_minirt *mrt, char **info)
{
	t_cylinder	*cylinder;

	cylinder = add_cylinder(mrt);
	if (!cylinder)
		return (R_MALLOC);
	if (!mrt_setcords(*info, cylinder->pos))
		return (mrt_error(INVL_CYLINDER_COORDINATES), R_INVALID);
	if (!mrt_setvector(*(++info), cylinder->vector))
		return (mrt_error(INVL_CYLINDER_VECTOR), R_INVALID);
	if (!mrt_setdouble(*(++info), &cylinder->diameter))
		return (mrt_error(INVL_CYLINDER_DIAMETER), R_INVALID);
	if (!mrt_setdouble(*(++info), &cylinder->height))
		return (mrt_error(INVL_CYLINDER_HEIGHT), R_INVALID);
	if (!mrt_setcolor(*(++info), cylinder->color))
		return (mrt_error(INVL_CYLINDER_COLOR), R_INVALID);
	if (*(++info))
		return (mrt_error(INVL_CYLINDER_INFO), R_INVALID);
	return (R_SUCCESS);
}
