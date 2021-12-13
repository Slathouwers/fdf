/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:16:20 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 13:31:55 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_swap_any(void *a, void *b, size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		return ;
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
}

int	add_color(int trgb, int r_add, int g_add, int b_add)
{
	int	t;
	int	r;
	int	g;
	int	b;

	t = get_t(trgb);
	r = get_r(trgb) + r_add;
	g = get_g(trgb) + g_add;
	b = get_b(trgb) + b_add;
	return (create_trgb(t, r, g, b));
}

int	get_z_color(double percent)
{
	int	r;
	int	g;
	int	b;

	r = get_r(COLOR_Z_MIN)
		+ (int) round(percent * (get_r(COLOR_Z_MIN) - get_r(COLOR_Z_MAX)));
	g = get_g(COLOR_Z_MIN)
		+ (int) round(percent * (get_g(COLOR_Z_MIN) - get_g(COLOR_Z_MAX)));
	b = get_b(COLOR_Z_MIN)
		+ (int) round(percent * (get_b(COLOR_Z_MIN) - get_b(COLOR_Z_MAX)));
	return (create_trgb(0, r, g, b));
}
