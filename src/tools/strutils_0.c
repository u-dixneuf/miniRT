#include "../../miniRT.h"

void	mrt_error(const char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	write(STDERR_FILENO, error_msg, mrt_strlen(error_msg));
}

u_int32_t	mrt_strlen(const char *s)
{
	u_int32_t	len;

	len = 0;
	while (s[len])
		len += 1;
	return (len);
}

