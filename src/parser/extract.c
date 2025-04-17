#include "../../miniRT.h"

t_id	extract_id(char *id)
{
	if (mrt_strcmp(id, "A"))
		return (ID_AMBIENT);
	if (mrt_strcmp(id, "L"))
		return (ID_LIGHT);
	if (mrt_strcmp(id, "C"))
		return (ID_CAMERA);
	if (mrt_strcmp(id, "sp"))
		return (ID_SPHERE);
	if (mrt_strcmp(id, "pl"))
		return (ID_PLANE);
	if (mrt_strcmp(id, "cy"))
		return (ID_CYLINDER);
	return (ID_INVALID);
}

t_return	extract_info(t_minirt *mrt, char **info)
{
	t_id	id;

	id = extract_id(*info);
	if (id == ID_AMBIENT)
		return (extract_ambient(mrt, ++info));
	else if (id == ID_CAMERA)
		return (extract_camera(mrt, ++info));
	else if (id == ID_LIGHT)
		return (extract_light(mrt, ++info));
	else if (id == ID_SPHERE)
		extract_sphere(mrt, ++info);
	else if (id == ID_PLANE)
		extract_plaextract_spheree(mrt, ++info);
	else if (id == ID_CYLINDER)
		extract_cylinder(mrt, ++info);
	else
		return (mrt_error(INVL_ID), R_INVALID);
	return (R_SUCCESS);
}

t_return	mrt_extract(t_minirt *mrt, char *line)
{
	t_return	ret;
	char		**info;

	if (!line || mrt_strlen(line) == 0)
		return (R_SUCCESS);
	info = mrt_split(line, " ");
	if (!info)
		return (mrt_error(LCNT_SPLT), R_FCNTSPLT);
	ret = extract_info(mrt, info);
	mrt_free_arr(info);
	if (ret == R_DBLCAPID)
		mrt_error(DBLCAPID);
	return (ret);
}
