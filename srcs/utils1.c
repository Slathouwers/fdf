/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:16:20 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/02 09:20:27 by slathouw         ###   ########.fr       */
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
