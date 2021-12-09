/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:52:48 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/09 11:35:42 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	t_mesh_init(t_mesh *m)
{
	ft_bzero(m, sizeof(t_mesh));
	ft_array_init(&m->arr_veritces, sizeof(t_vect));
	ft_array_init(&m->arr_edges, sizeof(t_point2d));
	m->edges = m->arr_edges.data;
	m->vertices = m->arr_veritces.data;
	la_matr_reset(&m->m);
}

int	t_mesh_add_vertex(t_mesh *m, t_vect v)
{
	ft_array_add(&m->arr_veritces, &v);
	m->vertices = m->arr_veritces.data;
	m->n_vertices = m->arr_veritces.count;
	return (m->n_vertices);
}

int	t_mesh_add_edge(t_mesh *m, t_point2d e)
{
	ft_array_add(&m->arr_edges, &e);
	m->edges = m->arr_edges.data;
	m->n_edges = m->arr_edges.count;
	return (m->n_edges);
}


static void center_and_rotate_mesh(t_mesh *m, t_vect size)
{
	int i;
	t_matr rotation;
	i = -1;
	while (++i < m->n_vertices)
	{
		m->vertices[i].x /= size.x - 1;
		m->vertices[i].y /= size.y - 1;
		m->vertices[i] = la_vect_sub(m->vertices[i], (t_vect){.5, .5, 0});
		m->vertices[i].y *= size.y - 1;
		m->vertices[i].y /= size.x - 1;
		m->vertices[i].x *= 500;
		m->vertices[i].y *= 500;
		m->vertices[i].z *= 10;
	}
	rotation = la_matr_rotation((t_vect) {0, 0, 1}, radians(45));
	i = -1;
	while (++i < m->n_vertices)
	{
		m->vertices[i] = la_vect_transform(m->vertices[i], rotation);
	}
}


t_mesh t_mesh_from_map(t_fdf *fdf)
{
	t_map *map;
	int x;
	int y;
	int z;
	t_mesh m;

	y = -1;
	t_mesh_init(&m);
	map = &fdf->map;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			z = map->z_data[y * map->width + x];
			t_mesh_add_vertex(&m, (t_vect){x, y, z});
			if (x > 0)
				t_mesh_add_edge(&m,
					(t_point2d){y * map->width + x, y * map->width + x - 1});
			if (y > 0)
				t_mesh_add_edge(&m,
					(t_point2d){y * map->width + x, (y - 1) * map->width + x});
		}
	}
	center_and_rotate_mesh(&m, (t_vect){map->width, map->height, 10.});
	return (m);
}
