/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:40:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/09 11:11:27 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

/*INIT*/
void	fdf_init(t_fdf *fdf)
{
	ft_bzero(fdf, sizeof(t_fdf));
	fdf->mlx = mlx_init();
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length,
			&fdf->endian);
	ft_printf("bits per pixel: %i | line length: %i | endian: %i |\n", fdf->bits_per_pixel, fdf->line_length, fdf->endian);
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
		t_cam_draw(&fdf.cam, &fdf, &fdf.mesh);
		mlx_put_image_to_window(fdf.mlx, fdf.mlx_win, fdf.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
}
/*----------*/