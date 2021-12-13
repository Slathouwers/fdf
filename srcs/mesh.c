/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:52:48 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 14:13:48 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	center_and_rotate_mesh(t_mesh *m, t_vect size)
{
	int		i;
	t_matr	rotation;

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
	rotation = la_matr_rotation((t_vect){0, 0, 1}, radians(45));
	i = -1;
	while (++i < m->n_vertices)
	{
		m->vertices[i] = la_vect_transform(m->vertices[i], rotation);
	}
}

static void	add_vertex_and_edge(t_map *map, t_mesh *m, t_vect v)
{
	int	x;
	int	y;

	x = (int) round(v.x);
	y = (int) round(v.y);
	t_mesh_add_vertex(m, v);
	if (x > 0)
		t_mesh_add_edge(m,
			(t_point2d){y * map->width + x, y * map->width + x - 1});
	if (y > 0)
		t_mesh_add_edge(m,
			(t_point2d){y * map->width + x, (y - 1) * map->width + x});
}

t_mesh	t_mesh_from_map(t_fdf *fdf)
{
	t_map	*map;
	int		x;
	int		y;
	int		z;
	t_mesh	m;

	y = -1;
	t_mesh_init(&m);
	map = &fdf->map;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			z = map->z_data[y * map->width + x];
			add_vertex_and_edge(map, &m, (t_vect){x, y, z});
		}
	}
	center_and_rotate_mesh(&m, (t_vect){map->width, map->height, 10.});
	return (m);
}
