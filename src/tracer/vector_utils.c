#include "../../miniRT.h"

double	vector_norme(double vector[3])
{
	double	norme;

	norme = vector[0] * vector[0];
	norme += vector[1] * vector[1];
	norme += vector[2] * vector[2];
	return (sqrt(norme));
}

void	set_vector(double vector[3], double x, double y, double z)
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
}

void	normalize_vector(double vector[3])
{
	double	norme;

	norme = vector_norme(vector);
	vector[0] = vector[0] / norme;
	vector[1] = vector[1] / norme;
	vector[2] = vector[2] / norme;
}

double	scalar_product(double vec_a[3], double vec_b[3])
{
	double	product;

	product = vec_a[0] * vec_b[0];
	product += vec_a[1] * vec_b[1];
	product += vec_a[2] * vec_b[2];
	return (product);
}

double	calc_distance(double pos_a[3], double pos_b[3])
{
	double	vector[3];
	
	vector[0] = pos_a[0] - pos_b[0];
	vector[1] = pos_a[1] - pos_b[1];
	vector[2] = pos_a[2] - pos_b[2];
	return (vector_norme(vector));
}
