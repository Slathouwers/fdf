/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:42:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/02 09:48:07 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../srcs/lin_alg/lin_alg.h"
# include "../libs/libftprintf/includes/ft_printf_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# ifndef M_PI
#  define M_PI 3.141592653589793115997963468544185161590576171875
# endif

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250
# define FOV 			120.

# define PROJ_PERSPECTIVE 1
# define PROJ_ISOMETRIC 0

/*STRUCTS*/
typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}		t_point;

typedef t_list	t_z_list;

typedef struct s_model
{
	int			width;
	int			height;
	t_z_list	*z_list;
	int			*z_arr;
	int			z_min;
	int			z_max;
	int			dz;
}		t_model;

/*
* v1 = y-axis rotation aka yaw
* v2 = x-axis rotation aka pitch
* v3 = x/z-axis translation aka camera movement
* proj = projection matrix
* disp = viewport matrix
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

typedef struct s_fdf
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_fdf;
/*----------*/

/*PROJECTIONS*/
t_matr		isometric_proj(double fov_width, double fov_height);
t_matr		perspective_proj(double n, double w, double h, double f);

/*CAMERA*/
/*SCREEN*/
void		pixel_put(t_fdf *data, int x, int y, int color);
void		put_line(t_fdf *data, t_point p0, t_point p1, int color);

/*UTILS*/
void		terminate(char *err_message);
int			get_index(int x, int y, int width);
double		radians(double degrees);
int			ft_isint(const char *str);
int			ft_abs(int v);
void		ft_swap(int *a, int *b);
int			add_color(int trgb, int r_add, int g_add, int b_add);

/*COLOR*/
int			create_trgb(int t, int r, int g, int b);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

#endif