/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 08:14:31 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/15 12:27:48 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_matr	isometric_proj(double fov_width, double fov_height)
{
	return ((t_matr){{
			{2. / fov_width, 0, 0, 0},
			{0, 2. / fov_height, 0, 0},
			{0, 0, 0, 0},
			{0, 0, 0, 1}}});
}

t_matr	perspective_proj(double n, double w, double h, double f)
{
	double	l;
	double	r;
	double	b;
	double	t;

	l = -w / 2;
	r = w / 2;
	b = -h / 2;
	t = h / 2;
	return ((t_matr){{
			{2 * n / (r - l), 0, (r + l) / (r - l), 0},
			{0, 2 * n / (t - b), (t + b) / (t - b), 0},
			{0, 0, -(f + n) / (f - n), -2 * f * n / (f - n)},
			{0, 0, -1, 0}}});
}
