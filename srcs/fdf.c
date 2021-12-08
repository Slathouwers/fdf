/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/08 08:46:14 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

/*TESTING*/
void	put_test_square(t_fdf *fdf)
{
	t_point2d	arr[4];

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

void	print_z_list(t_model *model)
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

void	print_z_arr(t_model *model)
{
	int	*ptr;
	int	x;
	int	y;
	
	ptr = model->z_arr;
	x = -1;
	y = -1;
	while (++y < model->height)
	{
		while (++x < model->width)
			ft_printf("val: %i| ", ptr[get_index(x, y, model->width)]);
		x = -1;
		ft_printf("\n");
	}
	ft_printf("Total = %i | Heigth = %i | Width = %i", get_index(0, y, model->width), model->height, model->width);
}

/*PARSING*/
void	set_z_arr(t_model *model)
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
	while (ptr)
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

t_z_list	*get_z_val(char *s)
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
		terminate("Map ERROR: line length inconsiteny!");
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
			terminate("Map ERROR: Memory insufficient!");
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
	fdf->w = WIDTH;
	fdf->h = HEIGHT;
	t_cam_init(&fdf->cam, (t_point2d){WIDTH, HEIGHT});
}

void	model_init(t_model *model)
{
	ft_bzero(model, sizeof(t_model));
}
/*-------*/

/*MAIN*/
int	main(int argc, char **argv)
{
//	int		fd;
	t_fdf	fdf;
//	t_model	model;

	(void) argv;

	errno = 0;
	if (argc == 2)
	{
	/* 	model_init(&model);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate("Map ERROR: No such file");
		if (!parse_model(&model, fd))
			terminate("Map ERROR: Parsing failed-> z_list empty");
		fdf_init(&fdf);
		print_z_arr(&model); */
		fdf_init(&fdf);
		fdf.mesh = t_mesh_cube(50);
		t_cam_draw(&fdf.cam, &fdf, &fdf.mesh);
		mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
}
/*----------*/