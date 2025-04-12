#ifndef	MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "src/libmlx/mlx.h"
# include "src/libmlx/mlx_int.h"

# define ARGS_NUM	"Incorrect number of args!\n"
# define FILE_OPN	"Could not open file!\n"
# define INVL_MAP	"Invalid map!\n"
# define MLX_INIT	"Could not init mlx session!\n"
# define WIN_INIT	"Could not create mlx window!\n"
# define IMG_INIT	"Could not create mlx image!\n"
# define IMG_ADDR	"Could not retrieve image address!\n"

# define WIDTH	200
# define HEIGHT	200

typedef enum e_return
{
	R_SUCCESS,
	R_MALLOC,
	R_INVALID,
	R_FILEDESC,
	R_LIBMLX
}	t_return;

typedef struct s_ambient
{
	double			ratio;
	int32_t			color[3];
}	t_ambient;

typedef struct s_camera
{
	double			pos[3];
	double			vector[3];
	int32_t			fov;
}	t_camera;

typedef struct s_light
{
	double			pos[3];
	double			ratio;
}	t_light;

typedef struct s_sphere
{
	double			pos[3];
	double			diameter;
	int32_t			color[3];
}	t_sphere;

typedef struct s_plane
{
	double			pos[3];
	double			vector[3];
	int32_t			color[3];
}	t_plane;

typedef struct s_cylinder
{
	double			pos[3];
	double			vector[3];
	double			diameter;
	double			height;
	int32_t			color[3];
}	t_cylinder;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;

	int				bpx;
	int				sl;
	int				e;

	char			*img_addr;
}	t_mlx;

typedef struct s_minirt
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	u_int32_t		n_sphere;
	t_sphere		*sphere;
	u_int32_t		n_plane;
	t_plane			*plane;
	u_int32_t		n_cylinder;
	t_cylinder		*cylinder;

	t_mlx			mlx;
}	t_minirt;

# define BUFFER_SIZE 20

typedef struct s_buff
{
	char			content[BUFFER_SIZE];
	ssize_t			length;
	char			end;
	struct s_buff	*next;
}	t_buff;

/* tools */
void		mrt_error(const char *error_msg);
u_int32_t	mrt_strlen(const char *s);

char		*mrt_getline(int fd);
void		link_check_buff(t_buff *p_plus, t_buff *p_buff);
char		*return_line(t_buff *p_plus);
void		free_buff(t_buff *p_plus);

void		mrt_memset(void *p, int c, u_int32_t size);
void		mrt_init(t_minirt *mrt);
void		mrt_free(void **p);
void		mrt_free_all(t_minirt *mrt);

t_return	mrt_initmlx(t_mlx *mlx);
void		mrt_freemlx(t_mlx mlx);

/* parser */
t_return	mrt_parser(const char *filename, t_minirt *mrt);

t_return	mrt_extract(int fd, t_minirt *mrt);

/* viewer */
t_return	mrt_viewer(t_minirt *mrt);

int			mrt_trace(t_minirt *mrt, int h, int w);

#endif