/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 08:19:36 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 13:33:02 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	print_z_arr(t_map *model)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++y < model->height)
	{
		while (++x < model->width)
			ft_printf("val: %i| ",
				model->z_data[get_rc_index(x, y, model->width)]);
		x = -1;
		ft_printf("\n");
	}
	ft_printf("Total = %i | Heigth = %i | Width = %i",
		get_rc_index(0, y, model->width), model->height, model->width);
}

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

/* t_mesh	t_mesh_cube(int size)
{
	t_mesh	m;
	int		i;

	i = -1;
	t_mesh_init(&m);
	t_mesh_add_vertex(&m, (t_vect){-1, -1, -1});
	t_mesh_add_vertex(&m, (t_vect){1, -1, -1});
	t_mesh_add_vertex(&m, (t_vect){1, 1, -1});
	t_mesh_add_vertex(&m, (t_vect){-1, 1, -1});
	t_mesh_add_vertex(&m, (t_vect){-1, -1, 1});
	t_mesh_add_vertex(&m, (t_vect){1, -1, 1});
	t_mesh_add_vertex(&m, (t_vect){1, 1, 1});
	t_mesh_add_vertex(&m, (t_vect){-1, 1, 1});
	t_mesh_add_edge(&m, (t_point2d){0, 1});
	t_mesh_add_edge(&m, (t_point2d){1, 2});
	t_mesh_add_edge(&m, (t_point2d){2, 3});
	t_mesh_add_edge(&m, (t_point2d){3, 0});
	t_mesh_add_edge(&m, (t_point2d){4, 5});
	t_mesh_add_edge(&m, (t_point2d){5, 6});
	t_mesh_add_edge(&m, (t_point2d){6, 7});
	t_mesh_add_edge(&m, (t_point2d){7, 4});
	t_mesh_add_edge(&m, (t_point2d){0, 4});
	t_mesh_add_edge(&m, (t_point2d){1, 5});
	t_mesh_add_edge(&m, (t_point2d){2, 6});
	t_mesh_add_edge(&m, (t_point2d){3, 7});
	while (++i < m.n_vertices)
		la_vect_scale(&m.vertices[i], size);
	return (m);
} */
