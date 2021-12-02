/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:42:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/02 09:05:10 by slathouw         ###   ########.fr       */
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

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250

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

#endif