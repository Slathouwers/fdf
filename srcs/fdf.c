/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 12:49:31 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

/*FRAME*/
void	frame_init(t_frame *f, void *mlx, int w, int h)
{
	f->img = mlx_new_image(mlx, w, h);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel, &f->line_length,
			&f->endian);
}

void	frame_clear(t_fdf *fdf)
{
	t_frame	*f;
	
	f = &fdf->f;
	ft_bzero(f->addr,
		((fdf->h - 1) * f->line_length + (fdf->w -1) * (f->bits_per_pixel / 8)));
}

/*INIT*/
void	fdf_init(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx = mlx_init();
	frame_init(&fdf->f, fdf->mlx, WIDTH, HEIGHT);
	ft_printf("bits per pixel: %i | line length: %i | endian: %i |\n", fdf->f.bits_per_pixel, fdf->f.line_length, fdf->f.endian);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->w = WIDTH;
	fdf->h = HEIGHT;
	t_cam_init(&fdf->cam, (t_point2d){WIDTH, HEIGHT});
}

/*-------*/

/*MAIN*/
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	fdf;

	errno = 0;
	if (argc == 2)
	{
		fdf_init(&fdf);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate("Map ERROR: No such file");
		if (!parse_map(&fdf.map, fd))
			terminate("Map ERROR: Parsing failed-> z_list empty");
		print_z_arr(&fdf.map);
		fdf.mesh = t_mesh_from_map(&fdf);
		fdf.time = clock();
		fdf.frame_time = clock();
		pixel_put(&fdf, WIDTH - 1, HEIGHT - 1, COLOR_Z_MAX);
		mlx_loop_hook(fdf.mlx, loop_hook, &fdf);
		bind_keys(fdf.mlx_win, &fdf);
		mlx_loop(fdf.mlx);
	}
}
/*----------*/
/* 
int	main(int argc, char **argv)
{
	int		fd;
	t_fdf	fdf;

	errno = 0;
	if (argc == 2)
	{
		fdf_init(&fdf);
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			terminate("Map ERROR: No such file");
		if (!parse_map(&fdf.map, fd))
			terminate("Map ERROR: Parsing failed-> z_list empty");
		print_z_arr(&fdf.map);
		fdf.mesh = t_mesh_from_map(&fdf);
		t_cam_draw(&fdf.cam, &fdf, &fdf.mesh);
		mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.f.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
} */