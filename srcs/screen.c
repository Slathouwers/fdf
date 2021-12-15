/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:01:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/15 14:35:38 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	unsigned int	*dst;

	dst = (unsigned int *) fdf->f.addr;
	if (x < 0 || y < 0 || x >= fdf->w || y >= fdf->h)
		return ;
	dst[y * fdf->w + x] = color;
}

static int
	set_up_direction(t_point2d *p0,
		t_point2d *p1, t_point2d *d, int (*error)[2])
{
	int	b_steep;

	b_steep = 0;
	if (ft_abs(p0->x - p1->x) < ft_abs(p0->y - p1->y))
	{
		ft_swap(&p0->x, &p0->y);
		ft_swap(&p1->x, &p1->y);
		b_steep = 1;
	}
	if (p0->x > p1->x)
	{
		ft_swap (&p0->x, &p1->x);
		ft_swap (&p0->y, &p1->y);
	}
	d->x = p1->x - p0->x;
	d->y = p1->y - p0->y;
	(*error)[0] = ft_abs(d->y) * 2;
	(*error)[1] = 0;
	return (b_steep);
}

static void	put_line_pixel(t_fdf *fdf, t_point2d curr, int color, int b_steep)
{
	if (b_steep)
		pixel_put(fdf, curr.y, curr.x, color);
	else
		pixel_put(fdf, curr.x, curr.y, color);
}

void
	put_line(t_fdf *data, t_point2d p0, t_point2d p1, int color)
{
	int			b_steep;
	t_point2d	d;
	int			error[2];
	t_point2d	curr;

 	if ((p0.x < 0 || p0.y < 0 || p0.x >= data->w || p0.y >= data->h)
		&& (p1.x < 0 || p1.y < 0 || p1.x >= data->w || p1.y >= data->h))
		return ;
	b_steep = set_up_direction(&p0, &p1, &d, &error);
	curr.y = p0.y;
	curr.x = p0.x - 1;
	while (++curr.x <= p1.x)
	{
		put_line_pixel(data, curr, color, b_steep);
		error[1] += error[0];
		if (error[1] > d.x)
		{
			if (p1.y > p0.y)
				curr.y++;
			else
				curr.y--;
			error[1] -= d.x * 2;
		}	
	}
}
