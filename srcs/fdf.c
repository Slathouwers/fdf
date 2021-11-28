/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/28 06:44:45 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;


int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int add_color(int trgb, int t_add, int r_add, int g_add, int b_add)
{
	int t;
	int r;
	int g;
	int b;

	t = get_t(trgb) + t_add;
	r = get_r(trgb) + r_add;
	g = get_g(trgb) + g_add;
	b = get_b(trgb) + b_add;
	return (create_trgb(t, r, g, b));
}



void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	square_put(t_data *img, int color, int size, int offset)
{
	int	i;

	i = offset - 1;
	while (++i < size + offset)
		pixel_put(img, i, offset, add_color(color, 0, i, 0, 0));
	i = offset - 1;
	while (++i < size + offset)
		pixel_put(img, offset, i, add_color(color, 0, 0, i, 0));
	i = offset - 1;
	while (++i < size + offset)
		pixel_put(img, size + offset, i, add_color(color, 0, 0, 0, i));
	i = offset - 1;
	while (++i < size + offset)
		pixel_put(img, i, size + offset, add_color(color, 0, i, 0, i));
}

/*Bresenham's line drawing algorithm*/
int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}

void ft_swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;	
}

void	put_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	b_steep;
	int	dx;
	int	dy;
	int	derror;
	int	error;
	int	x;
	int	y;
	
	b_steep = 0;
	if (ft_abs(x0 - x1) < ft_abs(y0 - y1))
	{
		ft_swap(&x0, &y0);
		ft_swap(&x1, &y1);
		b_steep = 1;
	}
	if (x0 > x1)
	{
		ft_swap (&x0, &x1);
		ft_swap (&y0, &y1);
	}
	dx = x1 - x0;
	dy = y1 - y0;
	derror = ft_abs(dy) * 2;
	error = 0;
	y = y0;
	x = x0 - 1;
	while (++x <= x1)
	{
		if (b_steep)
			pixel_put(data, y, x, color);
		else
			pixel_put(data, x, y, color);
		error += derror;
		if (error > dx)
		{
			if (y1 > y0)
				y++;
			else
				y--;
			error -= dx * 2;
		}	
	}
}
	/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
#include <stdio.h>
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	printf("bits per pixel: %i | line length: %i | endian: %i |\n", img.bits_per_pixel, img.line_length, img.endian);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FDF");
	//square_put(&img,0x00202020,150,20);
	put_line(&img, 10, 10, 10, 100, 0x0020FF20);
	put_line(&img, 10, 100, 100, 100, 0x00FF2020);
	put_line(&img, 100, 100, 100, 10, 0x002020FF);
	put_line(&img, 100, 10, 10, 10, 0x00FF20FF);
	put_line(&img, 10, 10, 100, 100, 0x0020FFFF);
	put_line(&img, 10, 100, 100, 10, 0x002020FF);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
