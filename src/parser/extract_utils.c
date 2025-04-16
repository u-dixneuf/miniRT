#include "../../miniRT.h"

t_return	extract_ambient(t_minirt *mrt, char **info)
{
	if (mrt->ambient.is_set)
		return (R_DBLCAPID);
	mrt->ambient.is_set = true;
	if (!mrt_getdouble(*info, &mrt->ambient.ratio)
		&& mrt->ambient.ratio >= 0.0 && mrt->ambient.ratio <= 1.0)
		return (mrt_error("[!!] Invalid Ambient Ratio\n"), R_INVALID);
	if (!mrt_setcolor(++(*info), &mrt->ambient.color)) // TODO
		return (mrt_error("[!!] Invalid Ambient Color\n"), R_INVALID);
	if (++info)
		return (mrt_error("[!!] Extra Ambient Info\n"), R_INVALID);
}

t_return	extract_camera(t_minirt *mrt, char **info)
{
	if (mrt->camera.is_set)
		return (R_DBLCAPID);
	mrt->camera.is_set = true;
	if (!mrt_getcord(++(*info), &mrt->camera.pos)) // TODO
		return (mrt_error("[!!] Invalid Camera Coordinates\n"), R_INVALID);
	if (!mrt_getvector(++(*info), &mrt->camera.vector)) //TODO
		return (mrt_error("[!!] Invalid Camera Vector\n"), R_INVALID);
	if (mrt_getcolor(++(*info), &mrt->camera.fov, 180))
		return (mrt_error("[!!] Invalid Camera FOV\n"), R_INVALID);
	if (++info)
		return (mrt_error("[!!] Extra Camera Info\n"), R_INVALID);
}

t_return extract_light(t_minirt *mrt, char **info)
{
	if (mrt->light.is_set)
		return (R_DBLCAPID);
	mrt->light.is_set = true;
	if (!mrt_getcord(++(*info), &mrt->light.pos)) // TODO
		return (mrt_error("[!!] Invalid Light Coordinates\n"), R_INVALID);
	if (!mrt_getdouble(*info, &mrt->light.ratio)
		&& mrt->ambient.ratio >= 0.0 && mrt->ambient.ratio <= 1.0)
		return (mrt_error("[!!] Invalid Light Ratio\n"), R_INVALID);
	if (++info)
		return (mrt_error("[!!] Extra Light Info\n"), R_INVALID);
}
