/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/15 12:44:23 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

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
		((fdf->h - 1) * f->line_length
			+ (fdf->w -1) * (f->bits_per_pixel / 8)));
}

void	fdf_init(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx = mlx_init();
	frame_init(&fdf->f, fdf->mlx, WIDTH, HEIGHT);
	fdf->mlx_win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->w = WIDTH;
	fdf->h = HEIGHT;
	init_cam(&fdf->cam, (t_point2d){WIDTH, HEIGHT});
}

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
			ft_terminate("Map ERROR: No such file");
		if (!parse_map(&fdf.map, fd))
			ft_terminate("Map ERROR: Parsing failed-> z_list empty");
		fdf.mesh = mesh_from_map(&fdf);
		fdf.time = clock();
		fdf.frame_time = clock();
		mlx_loop_hook(fdf.mlx, loop_hook, &fdf);
		bind_keys(fdf.mlx_win, &fdf);
		mlx_loop(fdf.mlx);
	}
}
