/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:54:58 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 12:58:27 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	close_hook(t_fdf *fdf)
{
//	mlx_destroy_image(fdf->mlx, fdf->f.img);
//	mlx_destroy_window(fdf->mlx, fdf->mlx_win);
	ft_int_array_del(&fdf->map.z_arr);
	ft_array_del(&fdf->mesh.arr_edges);
	ft_array_del(&fdf->mesh.arr_veritces);
	system("leaks fdf");
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
	t_cam_init_projection(&fdf->cam);
//	print_info(app);
}

static void	render(t_fdf *fdf)
{
	frame_clear(fdf);
	if (fdf->ctrl.status_prj
		&& fdf->ctrl.status_prj != fdf->ctrl.projection)
		ft_change_projection(fdf);
	t_cam_move(&fdf->cam, &fdf->ctrl);
	scroll_zoom(fdf);
	t_cam_draw(&fdf->cam, fdf, &fdf->mesh);
	mlx_put_image_to_window(fdf->mlx, fdf->mlx_win, fdf->f.img, 0, 0);
//	mlx_put_image_to_window(app->M, app->win,
//		app->framebuffer.image, app->sidebar_w, 0);
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
