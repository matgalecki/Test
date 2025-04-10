

#ifndef FDF_H

# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>

# define WINDOW_WIDTH 1300
# define WINDOW_HEIGHT 900
# define X_AXIS_ANGLE_ROTATION_RADIUS 0.610865
# define Z_AXIS_ANGLE_ROTATION_RADIUS 0.785398

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	uint32_t	color;
}				t_point;

typedef struct s_map
{
	t_point		**matrix;
	int			width;
	int			height;
	float		z_max;
}				t_map;

typedef struct s_cam
{
	float		scale;
	float		x_offset;
	float		y_offset;
	float		z_scale;
}				t_cam;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_cam		*cam;
}				t_fdf;

typedef struct s_line_drawing_data
{
	int			dx;
	int			dy;
	int			control;
	int			inc_x;
	int			inc_y;
}				t_line_drawing_data;

t_map			*parse_map(t_fdf *fdf, char *map_name);
int				validade_lines(int fd, int size);
uint32_t		put_alpha(uint32_t color);
void			clear_invalid_map(t_fdf *fdf, t_map *map);
float			get_scale(t_fdf *fdf);
void			center_to_origin(t_map *map);
void			draw_line(t_fdf *data, t_point start, t_point end);
void			put_pixel(t_fdf *fdf, int x, int y, uint32_t color);
void			render(t_fdf *fdf);
void			transformations(t_fdf *fdf, t_point start, t_point end);
void			scale(t_fdf *fdf, t_point *start, t_point *end);
void			isometric(t_fdf *fdf, t_point *start, t_point *end);
void			centralize(t_fdf *fdf, t_point *start, t_point *end);
void			set_background(t_fdf *fdf);
t_fdf			*new_fdf(char *map_name);
t_map			*new_map(void);
t_cam			*new_cam(t_fdf *fdf);
void			new_line_data(t_line_drawing_data *line_data, t_point start,
					t_point end);
void			error_handler(short exit_status);
void			validate_map_file(char *map_name);
t_point			**alloc_matrix(int width, int height);
void			free_matrix(t_map *map);
void			free_all(t_fdf *fdf);
void			close_window(void *param);

#endif