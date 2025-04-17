#include "../../miniRT.h"

t_sphere	*add_sphere(t_minirt *mrt)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)mrt_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (mrt_error("[!!] Failed to create Sphere node\n"), NULL);
	if (!mrt->sphere)
	{
		mrt->sphere = sphere;
		mrt->n_sphere++;
		return (sphere);
	}
	sphere->next = mrt->sphere;
	mrt->sphere = sphere;
	mrt->n_sphere++;
	return (sphere);
}

t_plane	*add_plane(t_minirt *mrt)
{
	t_plane	*plane;

	plane = (t_plane *)mrt_calloc(1, sizeof(t_plane));
	if (!plane)
		return (mrt_error("[!!] Failed to create Plane node\n"), NULL);
	if (!mrt->plane)
	{
		mrt->plane = plane;
		mrt->n_plane++;
		return (plane);
	}
	plane->next = mrt->plane;
	mrt->plane = plane;
	mrt->n_plane++;
	return (plane);
}

t_cylinder	*add_cylinder(t_minirt *mrt)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)mrt_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (mrt_error("[!!] Failed to create Cylinder node\n"), NULL);
	if (!mrt->cylinder)
	{
		mrt->cylinder = cylinder;
		mrt->n_cylinder++;
		return (cylinder);
	}
	cylinder->next = mrt->cylinder;
	mrt->cylinder = cylinder;
	mrt->n_cylinder++;
	return (cylinder);
}
