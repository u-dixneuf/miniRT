#ifndef	MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
#include <stdint.h>
# include <math.h>
// # include "src/libmlx/mlx.h"
// # include "src/libmlx/mlx_int.h"

# define ARGS_NUM	"[!!] Incorrect number of args!\n"

# define FILE_OPN	"[!!] Could not open file!\n"

# define FCNT_SPLT					"[!!] Could not split file content\n"
# define LCNT_SPLT					"[!!] Could not split line content\n"
# define CLR_SPLT					"[!!] Could not split colors\n"
# define CRD_SPLT					"[!!] Could not split coordinates\n"
# define VEC_SPLT					"[!!] Could not split vector\n"

# define INVL_EXT					"[!!] Invalid File Extention\n"
# define INVL_MAP					"[!!] Invalid Map!\n"
# define INVL_ID					"[!!] Invalid Identifier\n"

# define INVL_AMBIENT_RATIO			"[!!] Invalid Ambient Ratio\n"
# define INVL_AMBIENT_COLORS		"[!!] Invalid Ambient Color\n"
# define INVL_AMBIENT_INFO			"[!!] Extra Ambient Info\n"

# define INVL_CAMERA_COORDINATES	"[!!] Invalid Camera Coordinates\n"
# define INVL_CAMERA_VECTOR			"[!!] Invalid Camera Vector\n"
# define INVL_CAMERA_FOV			"[!!] Invalid Camera FOV\n"
# define INVL_CAMERA_INFO			"[!!] Extra Camera Info\n"

# define INVL_LIGHT_COORDINATES		"[!!] Invalid Light Coordinates\n"
# define INVL_LIGHT_RATIO			"[!!] Invalid Light Ratio\n"
# define INVL_LIGHT_INFO			"[!!] Extra Light Info\n"

# define INVL_SPHERE_COORDINATES	"[!!] Invalid Sphere Coordinates\n"
# define INVL_SPHERE_COLOR			"[!!] Invalid Sphere Color\n"
# define INVL_SPHERE_DIAMETER		"[!!] Invalid Sphere Diameter\n"
# define INVL_SPHERE_INFO			"[!!] Extra Sphere Info\n"

# define INVL_PLANE_COORDINATES		"[!!] Invalid Plan Coordinates\n"
# define INVL_PLANE_VECTOR			"[!!] Invalid Plane Vector\n"
# define INVL_PLANE_COLOR		  	"[!!] Invalid Plane Color\n"
# define INVL_PLANE_INFO			"[!!] Extra Plane Info\n"

# define INVL_CYLINDER_COORDINATES	"[!!] Invalid Cylinder Coordinates\n"
# define INVL_CYLINDER_VECTOR		"[!!] Invalid Cylinder Vector\n"
# define INVL_CYLINDER_DIAMETER		"[!!] Invalid Cylinder Diameter\n"
# define INVL_CYLINDER_HEIGHT		"[!!] Invalid Plane Height\n"
# define INVL_CYLINDER_COLOR		"[!!] Invalid Cylinder Color\n"
# define INVL_CYLINDER_INFO			"[!!] Extra Cylinder Info\n"

# define MLX_INIT					"[!!] Could not init mlx session!\n"
# define WIN_INIT					"[!!] Could not create mlx window!\n"
# define IMG_INIT					"[!!] Could not create mlx image!\n"
# define IMG_ADDR					"[!!] Could not retrieve image address!\n"

# define DBLCAPID	"[ii] Elements which are defined by a capital letter can only be declared once in the scene.\n"

# define SIZE	201

typedef enum e_return
{
	R_SUCCESS,
	R_FAILURE,
	R_MALLOC,
	R_INVALID,
	R_FILEDESC,
	R_FCNTSPLT,
	R_LIBMLX,
	R_DBLCAPID
}	t_return;

typedef enum e_id
{
	ID_AMBIENT,
	ID_CAMERA,
	ID_LIGHT,
	ID_SPHERE,
	ID_PLANE,
	ID_CYLINDER,
	ID_INVALID
}	t_id;

typedef enum e_type
{
	PLANE,
	SPHERE,
	CYLINDER
};

typedef struct s_ambient
{
	bool			is_set;
	double			ratio;
	uint32_t		color[3];
}	t_ambient;

typedef struct s_camera
{
	bool			is_set;
	double			pos[3];
	double			vector[3];
	uint32_t		fov;

	double			w_vector[3];
	double			h_vector[3];
}	t_camera;

typedef struct s_light
{
	bool			is_set;
	double			pos[3];
	double			ratio;
}	t_light;

typedef struct s_sphere
{
	struct s_sphere	*next;
	double			pos[3];
	double			diameter;
	uint32_t		color[3];
}	t_sphere;

typedef struct s_plane
{
	struct s_plane	*next;
	double			pos[3];
	double			vector[3];
	uint32_t		color[3];
}	t_plane;

typedef struct s_cylinder
{
	struct s_cylinder	*next;
	double				pos[3];
	double				vector[3];
	double				diameter;
	double				height;
	uint32_t			color[3];
}	t_cylinder;

typedef struct s_ray
{
	int				h;
	int				w;
	double			pos[3];
	double			vector[3];

	double			c_pos[3];
	int32_t			c_color[3];
	double			c_distance;
	bool			inside_obj;
	int				obj_type;

	int				color;
}	t_ray;

typedef struct s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;

	int32_t			bpx;
	int32_t			sl;
	int32_t			e;

	char			*img_addr;
}	t_mlx;

typedef struct s_minirt
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;

	uint32_t		n_sphere;
	t_sphere		*sphere;
	uint32_t		n_plane;
	t_plane			*plane;
	uint32_t		n_cylinder;
	t_cylinder		*cylinder;

	t_mlx			mlx;
}	t_minirt;

/* tools */
// stools
uint64_t	mrt_strlcpy(char *dst, const char *src, uint64_t dstsize);
uint64_t	mrt_strlcat(char *dst, const char *src, size_t size);
int32_t		mrt_strncmp(const char *s1, const char *s2, size_t n);
int32_t		mrt_strcmp(const char *s1, const char *s2);
bool		mrt_strchr(const char *s, int c);
char		*mrt_strrchr(const char *s, int c);
uint32_t	mrt_strlen(const char *s);
char		*mrt_strdup(const char *s);

bool		mrt_setdouble(char *str, double *nb);
bool		mrt_setuint32(char *str, uint32_t *value, uint32_t max);
bool		mrt_setcolor(char *str, uint32_t color[]);
bool		mrt_setcords(char *str, double cords[]);
bool		mrt_setvector(char *str, double vector[]);

char		**mrt_split(char const *s, char c);

void		mrt_error(const char *error_msg);
bool		mrt_isspace(int c);

// ftools;
# define	FREAD_SIZE 1024

char		*mrt_readfile(const char *filename);

// memtools
void		*mrt_calloc(size_t count, size_t size);
void		mrt_memset(void *p, int c, uint32_t size);
void		mrt_free(void **p);
void		mrt_free_arr(char **arr);
void		mrt_free_all(t_minirt *mrt);

// links
t_sphere	*add_sphere(t_minirt *mrt);
t_plane		*add_plane(t_minirt *mrt);
t_cylinder	*add_cylinder(t_minirt *mrt);

t_return	mrt_init(t_minirt *mrt);
t_return	mrt_initmlx(t_mlx *mlx);
void		mrt_freemlx(t_mlx mlx);

/* parser */
t_return	mrt_parser(const char *filename, t_minirt *mrt);

t_return	mrt_extract(t_minirt *mrt, char *line);
t_return	extract_ambient(t_minirt *mrt, char **info);
t_return	extract_camera(t_minirt *mrt, char **info);
t_return	extract_light(t_minirt *mrt, char **info);
t_return	extract_sphere(t_minirt *mrt, char **info);
t_return	extract_plane(t_minirt *mrt, char **info);
t_return	extract_cylinder(t_minirt *mrt, char **info);

/* viewer */
t_return	mrt_viewer(t_minirt *mrt);

double		vector_norme(double vector[3]);
void		set_vector(double vector[3], double x, double y, double z);
void		normalize_vector(double vector[3]);
double		scalar_product(double vec_a[3], double vec_b[3]);
double		calc_distance(double vec_a[3], double vec_b[3]);

void		get_first_vector(t_camera camera, t_ray *ray);
// void		get_second_vector(t_light light, ?);
void		check_sphere(t_ray *ray, uint32_t n, t_sphere *sphere);
void		check_plane(t_ray *ray, uint32_t n, t_plane *plane);
void		check_cylinder(t_ray *ray, uint32_t n, t_cylinder *cylinder);
void		get_color(t_ray *ray, t_ambient ambient, t_light light);

#endif