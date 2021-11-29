/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/11/29 13:25:16 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"



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

/*PUT IN LIBFT!!*/
int	ft_isint(const char *str)
{
	int			sign;
	int			i;
	long long	num;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((num * sign) <= 2147483647 && (num * sign) >= -2147483648);
}

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

	/*Bresenham's line drawing algorithm*/
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


/*PARSING*/

void set_z_arr(t_model *model)
{
	t_z_list	*ptr;
	size_t		i;
	size_t		arr_size;

	arr_size = model->width * model->height;
	model->z_arr = (int *)ft_calloc(arr_size, sizeof(int));
	if (!model->z_arr)
		exit(EXIT_FAILURE);
	i = 0;
	ptr = model->z_list;
	model->z_max = -2147483648;
	model->z_min = 2147483647;
	while(ptr)
	{
		model->z_arr[i] = *(int *)ptr->content;
		if (model->z_arr[i] > model->z_max)
			model->z_max = model->z_arr[i];
		if (model->z_arr[i] < model->z_min)
			model->z_min = model->z_arr[i];
		i++;
		ptr = ptr->next;
	}
	ft_lstclear(&model->z_list, &free);
	model->dz = model->z_max - model->z_min;
}

t_z_list *get_z_val(char *s)
{
	int	*i;
	if (!ft_isint(s))
		exit(EXIT_FAILURE);
	i = (int *) malloc(sizeof(int));
	*i = ft_atoi(s);
	return (ft_lstnew(i));
}
void	parse_split(char **split, t_model *model)
{
	int	width;

	width = 0;
	while (*split)
	{
		ft_lstadd_back(&model->z_list, get_z_val(*split));
		width++;
		split++;
	}
	if (!model->height)
		model->width = width;
	else if (model->width != width)
		exit(EXIT_FAILURE); //TODO: refactor to custom termination
}

int	parse_model(t_model *model, int fd)
{
	char	*line;
	char	**line_split;
	
	model->z_list = NULL;
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
	set_z_arr(model);
	return (1);
}
/*-------*/

void print_z_list(t_model *model)
{
	t_z_list	*ptr;
	int			width;
	
	ptr = model->z_list;
	width = model->width;
	while (ptr)
	{
		ft_printf("val: %i| ", *(int *)ptr->content);
		ptr = ptr->next;
		if (!--width)
		{
			ft_printf("\n");
			width = model->width;
		}
	}
	ft_printf("Total = %i | Heigth = %i | Width = %i", ft_lstsize(model->z_list), model->height, model->width);
}

void print_z_arr(t_model *model)
{
	t_z_list	*ptr;
	int			width;
	
	ptr = model->z_list;
	width = model->width;
	while (ptr)
	{
		ft_printf("val: %i| ", *(int *)ptr->content);
		ptr = ptr->next;
		if (!--width)
		{
			ft_printf("\n");
			width = model->width;
		}
	}
	ft_printf("Total = %i | Heigth = %i | Width = %i", ft_lstsize(model->z_list), model->height, model->width);
}
/*INIT*/
void	fdf_init(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx = mlx_init();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length,
			&fdf->endian);
	ft_printf("bits per pixel: %i | line length: %i | endian: %i |\n", fdf->bits_per_pixel, fdf->line_length, fdf->endian);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
}

void	model_init(t_model *model)
{
	ft_bzero(model, sizeof(t_model));
}
/*-------*/


/*MAIN*/
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	fdf;
	t_model	model;

	errno = 0;
	if (argc == 2)
	{
		model_init(&model);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE); //TODO: refactor to custom termination
		if (!parse_model(&model, fd))
			exit(EXIT_FAILURE); //TODO: refactor to custom termination
		fdf_init(&fdf);
		print_z_list(&model);
		mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
}
/*----------*/
