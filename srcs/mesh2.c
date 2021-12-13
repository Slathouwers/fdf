/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:39:28 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 14:52:33 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	mesh_init(t_mesh *m)
{
	ft_bzero(m, sizeof(t_mesh));
	ft_array_init(&m->arr_veritces, sizeof(t_vect));
	ft_array_init(&m->arr_edges, sizeof(t_point2d));
	m->edges = m->arr_edges.data;
	m->vertices = m->arr_veritces.data;
	la_matr_reset(&m->m);
}

int	add_vertex(t_mesh *m, t_vect v)
{
	ft_array_add(&m->arr_veritces, &v);
	m->vertices = m->arr_veritces.data;
	m->n_vertices = m->arr_veritces.count;
	return (m->n_vertices);
}

int	add_edge(t_mesh *m, t_point2d e)
{
	ft_array_add(&m->arr_edges, &e);
	m->edges = m->arr_edges.data;
	m->n_edges = m->arr_edges.count;
	return (m->n_edges);
}
