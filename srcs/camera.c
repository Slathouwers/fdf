/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:09:38 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/02 10:00:30 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/fdf.h"

void	t_cam_init_projection(t_cam *c)
{
	double	tg;
	double	near;
	double	ze;

	ze = exp(c->zoom / 100);
	tg = sin(radians(FOV / 2)) / cos(radians(FOV / 2)) * ze;
	near = 10.;
	if (c->projection_type == PROJ_PERSPECTIVE)
		c->proj = perspective_proj(near, tg * near,
				tg * near * HEIGHT / WIDTH,
				9999.);
	else
		c->proj = isometric_proj((double)WIDTH * ze,
				(double)HEIGHT * ze);
}

void	t_cam_init(t_cam *c, t_point display_res)
{
	int	w;
	int	h;

	w = display_res.x;
	h = display_res.y;
	la_matr_reset(&c->v3);
	la_matr_translate(&c->v3, (t_vect){0, 0, -400});
	c->v1 = (t_matr){{
	{1, 0, 0, 0},
	{0, 0, -1, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 1}}};
	la_matr_reset(&c->v2);
	c->disp = (t_matr){{
	{.5 * w, 0, 0, .5 * w},
	{0, .5 * h, 0, .5 * h},
	{0, 0, 0, 0},
	{0, 0, 0, 1}}};
	c->zoom = 0;
	c->projection_type = PROJ_PERSPECTIVE;
	t_cam_init_projection(c);
}

void	t_cam_draw(t_cam *cam, void *p, t_mesh *mesh)
{
	int		i;
	t_vect	p1;
	t_vect	p2;
	t_matr	m;

	m = mesh->m;
	m = la_matr_mul(cam->v1, m);
	m = la_matr_mul(cam->v2, m);
	m = la_matr_mul(cam->v3, m);
	m = la_matr_mul(cam->proj, m);
	i = -1;
	while (++i < mesh->n_edges)
	{
		p1 = mesh->vertices[mesh->edges[i].x].v;
		p2 = mesh->vertices[mesh->edges[i].y].v;
		p1 = la_vect_transform_div_w(p1, m);
		if (p1.z < -1. || p1.z > 1.)
			continue ;
		p2 = la_vect_transform_div_w(p2, m);
		if (p2.z < -1. || p2.z > 1.)
			continue ;
		p1 = la_vect_transform(p1, cam->disp);
		p2 = la_vect_transform(p2, cam->disp);
		line(p, p1, p2, (uint)(255 * GREEN));
	}
}
/*
void	t_cam_move(t_cam *cam, t_controller *ctrl)
{
	int mouse_dx;
	int mouse_dy;

	if (ctrl->d_yaw)
	{
		cam->v1 = t_mat_mul(cam->v1, t_mat_rot(
				(t_vec){0, 0, 1},
				radians(ctrl->d_yaw)));
	}
	if (ctrl->d_pitch)
	{
		cam->v2 = t_mat_mul(cam->v2, t_mat_rot(
				(t_vec){1, 0, 0},
				radians(ctrl->d_pitch)));
	}
	if (ctrl->v.x || ctrl->v.z)
	{
		t_mat_translate(&cam->v3, ctrl->v);
	}
	if (ctrl->d_zoom)
	{
		cam->zoom += ctrl->d_zoom;
		t_cam_init_projection(cam);
	}
	if (ctrl->mouse.buttons[MOUSE_B_LEFT])
	{
		mouse_dx = ctrl->mouse.click_pos[MOUSE_B_LEFT].x - ctrl->mouse.pos.x;
		mouse_dy = ctrl->mouse.click_pos[MOUSE_B_LEFT].y - ctrl->mouse.pos.y;
		cam->v1 = t_mat_mul(cam->v1, t_mat_rot(
				(t_vec){0, 0, 1},
				radians((double)mouse_dx / 100)));
		cam->v2 = t_mat_mul(cam->v2, t_mat_rot(
				(t_vec){1, 0, 0},
				radians((double)mouse_dy / 100)));
	}
}
*/