/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/29 10:12:07 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

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

/*COLOR*/
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
/*----------*/

/*DRAW*/
void	pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int
	set_up_direction(t_point *p0, t_point *p1, t_point *d, int (*error)[2])
{
	int	b_steep;

	b_steep = 0;
	if (ft_abs(p0->x - p1->x) < ft_abs(p0->y - p1->y))
	{
		ft_swap(&p0->x, &p0->y);
		ft_swap(&p1->x, &p1->y);
		b_steep = 1;
	}
	if (p0->x > p1->x)
	{
		ft_swap (&p0->x, &p1->x);
		ft_swap (&p0->y, &p1->y);
	}
	d->x = p1->x - p0->x;
	d->y = p1->y - p0->y;
	(*error)[0] = ft_abs(d->y) * 2;
	(*error)[1] = 0;
	return (b_steep);
}

void	put_line(t_fdf *data, t_point p0, t_point p1, int color)
{
	int		b_steep;
	t_point	d;
	int		error[2];
	t_point	curr;

	b_steep = set_up_direction(&p0, &p1, &d, &error);
	curr.y = p0.y;
	curr.x = p0.x - 1;
	while (++curr.x <= p1.x)
	{
		if (b_steep)
			pixel_put(data, curr.y, curr.x, color);
		else
			pixel_put(data, curr.x, curr.y, color);
		error[1] += error[0];
		if (error[1] > d.x)
		{
			if (p1.y > p0.y)
				curr.y++;
			else
				curr.y--;
			error[1] -= d.x * 2;
		}	
	}
}
	/*----------*/
/*----------*/

/*TESTING*/
void	put_test_square(t_fdf *fdf)
{
	t_point	arr[4];

	arr[0].x = 10;
	arr[0].y = 10;
	arr[1].x = 10;
	arr[1].y = 100;
	arr[2].x = 100;
	arr[2].y = 100;
	arr[3].x = 100;
	arr[3].y = 10;
	put_line(fdf, arr[0], arr[1], 0x0020FF20);
	put_line(fdf, arr[1], arr[2], 0x00FF2020);
	put_line(fdf, arr[2], arr[3], 0x002020FF);
	put_line(fdf, arr[3], arr[0], 0x00FF20FF);
	put_line(fdf, arr[0], arr[2], 0x0020FFFF);
	put_line(fdf, arr[1], arr[3], 0x002020FF);
}
/*-------*/

/*INIT*/
void	fdf_init(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length,
			&fdf->endian);
	printf("bits per pixel: %i | line length: %i | endian: %i |\n", fdf->bits_per_pixel, fdf->line_length, fdf->endian);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
}
/*-------*/

/*PARSING*/
void	parse_split(char **split, t_model *model)
{
	
}

int	parse_model(t_model *model, int fd)
{
	char	*line;
	char	**line_split;
	
	line = get_next_line(fd);
	while (line)
	{
		line_split = ft_split(line, ' ');
		if (!line_split)
			exit(EXIT_FAILURE); //TODO: refactor to custom termination
		parse_split(line_split, model);
		ft_free_split(line_split);
		free(line);
		line = get_next_line(fd);
		model->height++;
	}
	if(!model->z_list)
		return (0);
	return (1);
}
/*-------*/

/*MAIN*/
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	fdf;
	t_model	model;

	errno = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE); //TODO: refactor to custom termination
		if (!parse_model(&model, fd))
			exit(EXIT_FAILURE); //TODO: refactor to custom termination
		fdf_init(&fdf);
		put_test_square(&fdf);
		mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
}
/*----------*/
