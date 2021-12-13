/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:42:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 12:47:25 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../srcs/lin_alg/lin_alg.h"
# include "../srcs/ft_array/ft_array.h"
# include "../libs/libftprintf/includes/ft_printf_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <time.h>

# ifndef M_PI
#  define M_PI 3.141592653589793115997963468544185161590576171875
# endif

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250
# define FOV 			120.

# define FRAME_RATE 	60
# define FRAME_TIME 	1./60

# define PROJ_PERSPECTIVE 1
# define PROJ_ISOMETRIC 0

# define COLOR_Z_MAX	0x00FF8C00
# define COLOR_Z_MIN	0x00008B8B

# define MLX_EVENT_KEY_PRESS 2
# define MLX_EVENT_KEY_PRESS_MASK 1L<<0
# define MLX_EVENT_KEY_RELEASE 3
# define MLX_EVENT_KEY_RELEASE_MASK 1L<<1
# define MLX_EVENT_MOUSE_PRESS 4
# define MLX_EVENT_MOUSE_PRESS_MASK  1L<<2	
# define MLX_EVENT_MOUSE_RELEASE 5
# define MLX_EVENT_MOUSE_RELEASE_MASK 1L<<3
# define MLX_EVENT_MOUSE_MOVE 6
# define MLX_EVENT_MOUSE_MOVE_MASK 1L<<6
# define MLX_EVENT_EXPOSE 12
# define MLX_EVENT_EXIT 17

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_ESC 53
# define KEY_I 34
# define KEY_P 35
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_HOME 115
# define KEY_END 119
# define LIN_KEY_LEFT 65361
# define LIN_KEY_RIGHT 65363
# define LIN_KEY_DOWN 65364
# define LIN_KEY_UP 65362
# define LIN_KEY_ESC 65307
# define MOUSE_B_LEFT  1
# define MOUSE_B_RIGHT  2
# define MOUSE_B_MIDDLE  3
# define MOUSE_SCROLL_UP  4
# define MOUSE_SCROLL_DOWN  5
# define MOUSE_SCROLL_LEFT  6
# define MOUSE_SCROLL_RIGHT  7

/*STRUCTS*/

//TODO: Refactor t_vect to t_vert
typedef struct s_vert
{
	t_vect		v;
	int			color;
}				t_vert;

typedef struct s_point2d
{
	int	x;
	int	y;
}		t_point2d;

typedef struct s_mesh
{
	t_vect		*vertices;
	t_array		arr_veritces;
	t_array		arr_edges;
	int			n_vertices;
	t_point2d	*edges;
	int			n_edges;
	t_matr		m;
}				t_mesh;

//TODO: IMPLEMENT CONTROLER
typedef struct	s_mouse
{
	int 		buttons[8];
	t_point2d 	pos;
	t_point2d 	click_pos[8];
	t_point2d 	release_pos[8];
} t_mouse;

typedef struct s_ctrl
{
	int		keyboard[128];
	t_mouse	mouse;
	double	d_yaw;
	double	d_pitch;
	double	d_tilt;
	int		d_scroll;
	int		status_prj;
	int		d_zoom;
	int		projection;
	t_vect	v;
}			t_ctrl;

typedef struct s_map
{
	int			width;
	int			height;
	t_int_array	z_arr;
	int			*z_data;
	int			z_min;
	int			z_max;
	int			dz;
}		t_map;

/* t_cam:
*	double zoom = exponent for current zoom calculations
* 	int projection_type = 1 for perspective, 0 for isometric
*	t_matr v1 = y-axis rotation matrix aka yaw
* 	t_matr v2 = x-axis rotation aka pitch
* 	t_matr v3 = x/z-axis translation aka camera movement
* 	t_matr proj = projection matrix
* 	t_matr disp = viewport matrix
*/
typedef struct s_cam
{
	double	zoom;
	int		projection_type;
	t_matr	v1;
	t_matr	v2;
	t_matr	v3;
	t_matr	proj;
	t_matr	disp;
}			t_cam;

typedef struct s_frame
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;	
}	t_frame;

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_win;
	int		w;
	int		h;
	double	z_scale;
	time_t	time;
	time_t	frame_time;
	t_frame	f;
	t_cam	cam;
	t_mesh	mesh;
	t_map	map;
	t_ctrl	ctrl;
}	t_fdf;
/*----------*/

/*3D MESH*/
void		t_mesh_init(t_mesh *m);
int			t_mesh_add_vertex(t_mesh *m, t_vect v);
int			t_mesh_add_edge(t_mesh *m, t_point2d e);
t_mesh		t_mesh_from_map(t_fdf *fdf);

/*PROJECTIONS*/
t_matr		isometric_proj(double fov_width, double fov_height);
t_matr		perspective_proj(double n, double w, double h, double f);

/*CAMERA*/
void	t_cam_init_projection(t_cam *c);
void	t_cam_init(t_cam *c, t_point2d display_res);
void	t_cam_draw(t_cam *cam, t_fdf *fdf, t_mesh *mesh);
void	t_cam_move(t_cam *cam, t_ctrl *ctrl);

/*SCREEN*/
void		pixel_put(t_fdf *data, int x, int y, int color);
void		put_line(t_fdf *data, t_point2d p0, t_point2d p1, int color);

/*UTILS*/
	/*TO LIBFT!!*/
void		terminate(char *err_message);
int			get_rc_index(int r, int c, int width);
double		radians(double degrees);
int			ft_isint(const char *str);
int			ft_abs(int v);
void		ft_swap(int *a, int *b);
void		ft_swap_any(void *a, void *b, size_t size);
	/*----------*/
int			add_color(int trgb, int r_add, int g_add, int b_add);
/*-----------*/

/*COLOR*/
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);
int			get_z_color(double percent);

/*PARSE MAP*/
int			parse_map(t_map *model, int fd);

/*CONTROL HOOKS*/
void		bind_keys(void *win, t_fdf *fdf);
int			close_hook(t_fdf *fdf);
void		ctrl_update_state(t_fdf *fdf);
int			ctrl_mouse_press(int button, int x, int y, t_fdf *fdf);
int			ctrl_mouse_release(int button, int x, int y, t_fdf *fdf);
int			ctrl_mouse_move(int x, int y, t_fdf *fdf);
int			ctrl_key_press(int keycode, t_fdf *fdf);
int			ctrl_key_release(int keycode, t_fdf *fdf);

/*FRAMERATE*/
int			loop_hook(void *p);
/*TESTING UTILS*/
void		print_z_arr(t_map *model);
void		put_test_square(t_fdf *fdf);
t_mesh		t_mesh_cube(int size);

void		frame_clear(t_fdf	*fdf);

#endif