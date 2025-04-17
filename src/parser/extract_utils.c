#include "../../miniRT.h"

t_return	extract_ambient(t_minirt *mrt, char **info)
{
	if (mrt->ambient.is_set)
		return (R_DBLCAPID);
	mrt->ambient.is_set = true;
	if (!mrt_setdouble(*info, &mrt->ambient.ratio)
		&& mrt->ambient.ratio >= 0.0 && mrt->ambient.ratio <= 1.0)
		return (mrt_error(INVL_AMBIENT_RATIO), R_INVALID);
	if (!mrt_setcolor(++(*info), &mrt->ambient.color))
		return (mrt_error(INVL_AMBIENT_COLORS), R_INVALID);
	if (++info)
		return (mrt_error(INVL_AMBIENT_INFO), R_INVALID);
}

t_return	extract_camera(t_minirt *mrt, char **info)
{
	if (mrt->camera.is_set)
		return (R_DBLCAPID);
	mrt->camera.is_set = true;
	if (!mrt_setcords(++(*info), &mrt->camera.pos))
		return (mrt_error(INVL_CAMERA_COORDINATES), R_INVALID);
	if (!mrt_setvector(++(*info), &mrt->camera.vector))
		return (mrt_error(INVL_CAMERA_VECTOR), R_INVALID);
	if (mrt_setuint32(++(*info), &mrt->camera.fov, 180))
		return (mrt_error(INVL_CAMERA_FOV), R_INVALID);
	if (++info)
		return (mrt_error(INVL_CAMERA_INFO), R_INVALID);
}

t_return extract_light(t_minirt *mrt, char **info)
{
	if (mrt->light.is_set)
		return (R_DBLCAPID);
	mrt->light.is_set = true;
	if (!mrt_setcords(++(*info), &mrt->light.pos))
		return (mrt_error(INVL_LIGHT_COORDINATES), R_INVALID);
	if (!mrt_setdouble(*info, &mrt->light.ratio)
		&& mrt->light.ratio >= 0.0 && mrt->light.ratio <= 1.0)
		return (mrt_error(INVL_LIGHT_RATIO), R_INVALID);
	if (++info)
		return (mrt_error(INVL_LIGHT_INFO), R_INVALID);
}
