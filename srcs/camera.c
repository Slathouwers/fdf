/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:09:38 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/15 12:56:05 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	init_proj(t_cam *c)
{
	double	far;
	double	near;
	double	ze;

	ze = exp(c->zoom / 100);
	far = cos(ft_radians(FOV / 2)) / sin(ft_radians(FOV / 2)) * ze * 2;
	near = 100.;
	if (c->projection_type == PROJ_PERSPECTIVE)
		c->proj = perspective_proj(near, far * near,
				far * near * HEIGHT / WIDTH,
				9999.);
	else
		c->proj = isometric_proj((double)WIDTH * ze * 1,
				(double)HEIGHT * ze * 1);
}

void	init_cam(t_cam *c, t_point2d display_res)
{
	int	w;
	int	h;

	w = display_res.x;
	h = display_res.y;
	la_matr_reset(&c->v3);
	la_matr_translate(&c->v3, (t_vect){0, 0, -800});
	c->v1 = (t_matr){{
	{1, 0, 0, 0},
	{0, 0, -1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1}}};
	la_matr_reset(&c->v2);
	c->v2 = la_matr_mul(c->v2, la_matr_rotation(
				(t_vect){1, 0, 0},
				-0.4));
	c->disp = (t_matr){{
	{.5 * w, 0, 0, .5 * w},
	{0, .5 * h, 0, .5 * h},
	{0, 0, 0, 0},
	{0, 0, 0, 1}}};
	c->zoom = 0;
	c->projection_type = PROJ_ISOMETRIC;
	init_proj(c);
}

static int	project_edge(t_fdf *fdf, t_matr m, t_vect v1, t_vect v2)
{
	t_point2d	p1;
	t_point2d	p2;
	t_cam		*cam;

	cam = &fdf->cam;
	v1 = la_vect_transform_div_w(v1, m);
	if (v1.z < -1. || v1.z > 1.)
		return (0);
	v2 = la_vect_transform_div_w(v2, m);
	if (v2.z < -1. || v2.z > 1.)
		return (0);
	v1 = la_vect_transform(v1, cam->disp);
	p1 = (t_point2d){(int) round(v1.x), (int) round(v1.y)};
	v2 = la_vect_transform(v2, cam->disp);
	p2 = (t_point2d){(int) round(v2.x), (int) round(v2.y)};
	put_line(fdf, p1, p2, COLOR_Z_MAX);
	return (1);
}

void	draw_proj(t_cam *cam, t_fdf *fdf, t_mesh *mesh)
{
	int			i;
	t_vect		v1;
	t_vect		v2;
	t_matr		m;
	int			edge_count;

	m = mesh->m;
	m = la_matr_mul(cam->v1, m);
	m = la_matr_mul(cam->v2, m);
	m = la_matr_mul(cam->v3, m);
	m = la_matr_mul(cam->proj, m);
	i = -1;
	edge_count = 0;
	while (++i < mesh->n_edges)
	{
		v1 = mesh->vertices[mesh->edges[i].x];
		v2 = mesh->vertices[mesh->edges[i].y];
		edge_count += project_edge(fdf, m, v1, v2);
	}
}

void	update_proj(t_cam *cam, t_ctrl *ctrl)
{
	int	mouse_dx;
	int	mouse_dy;

	if (ctrl->d_yaw)
		cam->v1 = la_matr_mul(cam->v1, la_matr_rotation((t_vect){0, 0, 1},
					ft_radians(ctrl->d_yaw)));
	if (ctrl->d_pitch)
		cam->v2 = la_matr_mul(cam->v2, la_matr_rotation((t_vect){1, 0, 0},
					ft_radians(ctrl->d_pitch)));
	if (ctrl->v.x || ctrl->v.z)
		la_matr_translate(&cam->v3, ctrl->v);
	if (ctrl->d_zoom)
	{
		cam->zoom += ctrl->d_zoom;
		init_proj(cam);
	}
	if (ctrl->mouse.buttons[MOUSE_B_LEFT])
	{
		mouse_dx = ctrl->mouse.click_pos[MOUSE_B_LEFT].x - ctrl->mouse.pos.x;
		mouse_dy = ctrl->mouse.click_pos[MOUSE_B_LEFT].y - ctrl->mouse.pos.y;
		cam->v1 = la_matr_mul(cam->v1, la_matr_rotation((t_vect){0, 0, 1},
					ft_radians((double)mouse_dx / 100)));
		cam->v2 = la_matr_mul(cam->v2, la_matr_rotation((t_vect){1, 0, 0},
					ft_radians((double)mouse_dy / 100)));
	}
}
