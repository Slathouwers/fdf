/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:52:48 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/08 08:40:48 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_mesh	t_mesh_cube(int size)
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
}

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
