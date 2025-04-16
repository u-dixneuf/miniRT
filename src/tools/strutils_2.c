#include "../../miniRT.h"

static bool	is_digit(int c)
{
	return (c >= 48 && c <= 57);
}

static bool	get_fraction(char *str, double *nb)
{
	double	div;

	div = 0.1;
	if (*str == '.')
		str++;
	while (*str && is_digit(*str))
	{
		*nb = *nb + ((*str - '0') * div);
		div *= 0.1;
		str++;
	}
	while (is_space(*str))
		str++;
	if (*str)
		return (false);
	return (true);
}

bool	mrt_getdouble(char *str, double *nb)
{
	int	sign;

	if (!str)
		return (false);
	*nb = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && is_digit(*str) && *str != '.')
	{
		*nb = (*nb * 10.0) + (*str - '0');
		str++;
	}
	if (!get_fraction(str, nb))
		return (false);
	*nb *= sign;
	return (true);
}

bool	mrt_getcolor(char *str, uint32_t *value, int32_t max)
{
	uint32_t	res;

	if (!str)
		return (false);
	res = 0;
	if (*str == '-')
		return (false);
	if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		res = (*str - 48) + (res * 10);
		str++;
	}
	if (res > max)
		return (false);
	*value = res;
	return (true);
}