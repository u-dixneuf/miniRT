#include "../../miniRT.h"

static bool	get_fraction(char *str, double *nb)
{
	double	div;

	div = 0.1;
	if (*str == '.')
		str++;
	while (*str && *str >= 48 && *str <= 57)
	{
		*nb = *nb + ((*str - '0') * div);
		div *= 0.1;
		str++;
	}
	while (mrt_isspace(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

bool	mrt_setdouble(char *str, double *nb)
{
	int	sign;

	if (!str)
		return (false);
	*nb = 0;
	sign = 1;
	while (mrt_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= 48 && *str <= 57 && *str != '.')
	{
		*nb = (*nb * 10.0) + (*str - '0');
		str++;
	}
	if (!get_fraction(str, nb))
		return (false);
	*nb *= sign;
	return (true);
}

bool	mrt_setuint32(char *str, uint32_t *value, uint32_t max)
{
	uint32_t	res;

	if (!str)
		return (false);
	res = 0;
	if (*str == '-')
		return (false);
	if (*str == '+')
		str++;
	while (*str && *str >= 48 && *str <= 57)
	{
		res = (*str - 48) + (res * 10);
		str++;
	}
	if (*str || res > max)
		return (false);
	*value = res;
	return (true);
}

bool	mrt_setcolor(char *str, uint32_t color[])
{
	char	**colors;
	char	**s;

	colors = mrt_split(str, ',');
	if (!colors)
		return (mrt_error(CLR_SPLT), false);
	s = colors;
	if (!mrt_setuint32(*colors, &color[0], 255))
		return (mrt_free_arr(s), false);
	if (!mrt_setuint32(*(++colors), &color[1], 255))
		return (mrt_free_arr(s), false);
	if (!mrt_setuint32(*(++colors), &color[2], 255))
		return (mrt_free_arr(s), false);
	if (*(++colors))
		return (mrt_free_arr(colors), false);
	return (mrt_free_arr(s), true);
}

bool	mrt_setcords(char *str, double	cord[])
{
	char	**cords;
	char	**s;

	cords = mrt_split(str, ',');
	if (!cords)
		return (mrt_error(CRD_SPLT), false);
	s = cords;
	if (!mrt_setdouble(*cords, &cord[0]))
		return (mrt_free_arr(s), false);
	if (!mrt_setdouble(*(++cords), &cord[1]))
		return (mrt_free_arr(s), false);
	if (!mrt_setdouble(*(++cords), &cord[2]))
		return (mrt_free_arr(s), false);
	if (*(++cords))
		return (mrt_free_arr(cords), false);
	return (mrt_free_arr(s), true);
}

bool	mrt_setvector(char *str, double vector[])
{
	char	**v;
	char	**s;

	v = mrt_split(str, ',');
	if (!v)
		return (mrt_error(VEC_SPLT), false);
	s = v;
	if (!mrt_setdouble(*v, &vector[0]) || (vector[0] > 1.0 || vector[0] < -1.0))
		return (mrt_free_arr(s), false);
	if (!mrt_setdouble(*(++v), &vector[1]) || (vector[1] > 1.0 || vector[1] < -1.0))
		return (mrt_free_arr(s), false);
	if (!mrt_setdouble(*(++v), &vector[2]) || (vector[2] > 1.0 || vector[2] < -1.0))
		return (mrt_free_arr(s), false);
	if (*(++v))
		return (mrt_free_arr(s), false);
	return (mrt_free_arr(s), true);
}
