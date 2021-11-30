/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:42:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/30 12:42:09 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../libs/libftprintf/includes/ft_printf_bonus.h"
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
/* <stdio.h> for perror() */
# include <stdio.h>

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

#endif