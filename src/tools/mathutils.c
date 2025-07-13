#include "../../miniRT.h"

bool	quadratic(double p[3])
{
	double	delta;
	double	t[2];

	delta = pow(p[1], 2) - 4 * p[0] * p[2];
	if (delta >= 0)
	{
		t[0] = (-p[1] - sqrt(delta)) / (2 * p[0]);
		t[1] = (-p[1] + sqrt(delta)) / (2 * p[0]);
		if (fabs(t[0]) <= fabs(t[1]))
		{
			p[0] = t[0];
			p[1] = t[1];
		}
		else
		{
			p[0] = t[1];
			p[1] = t[0];
		}
		return (true);
	}
	return (false);
}
