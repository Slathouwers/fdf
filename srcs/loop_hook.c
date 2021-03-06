/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:54:58 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 15:02:26 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	close_hook(t_fdf *fdf)
{
	ft_int_array_del(&fdf->map.z_arr);
	ft_array_del(&fdf->mesh.arr_edges);
	ft_array_del(&fdf->mesh.arr_veritces);
	exit(0);
}

static void	scroll_zoom(t_fdf *fdf)
{
	if (fdf->ctrl.d_scroll)
	{
		fdf->z_scale += fdf->ctrl.d_scroll;
		fdf->mesh.m.elms[2][2] = exp(fdf->z_scale / 100);
	}
}

static void	ft_change_projection(t_fdf *fdf)
{
	fdf->ctrl.projection = fdf->ctrl.status_prj;
	if (fdf->ctrl.status_prj == 1)
		fdf->cam.projection_type = PROJ_PERSPECTIVE;
	else
		fdf->cam.projection_type = PROJ_ISOMETRIC;
	init_proj(&fdf->cam);
}

static void	render(t_fdf *fdf)
{
	frame_clear(fdf);
	if (fdf->ctrl.status_prj
		&& fdf->ctrl.status_prj != fdf->ctrl.projection)
		ft_change_projection(fdf);
	update_proj(&fdf->cam, &fdf->ctrl);
	scroll_zoom(fdf);
	draw_proj(&fdf->cam, fdf, &fdf->mesh);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->f.img, 0, 0);
}

int	loop_hook(void *p)
{
	t_fdf	*fdf;
	double	dt;

	fdf = p;
	fdf->time = clock();
	dt = (double)(fdf->time - fdf->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		fdf->frame_time = fdf->time;
		render(fdf);
	}
	return (0);
}
