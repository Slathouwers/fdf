/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 12:23:08 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 12:26:06 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_matr	*la_matr_add_ref(t_matr *a, t_matr *b)
{
	int	i;
	int	j;

	i = -1;
	while (++i < LA_RANK)
	{
		j = -1;
		while (++j < LA_RANK)
		{
			a->elms[i][j] += b->elms[i][j];
		}
	}
	return (a);
}

t_matr	la_matr_mul(t_matr a, t_matr b)
{
	t_matr	r;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < LA_RANK)
	{
		j = -1;
		while (++j < LA_RANK)
		{
			r.elms[i][j] = 0;
			k = -1;
			while (++k < LA_RANK)
			{
				r.elms[i][j] += a.elms[i][k] * b.elms[k][j];
			}
		}
	}
	return (r);
}

t_matr	la_matr_mul_ref(t_matr *a, t_matr *b)
{
	t_matr	r;
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < LA_RANK)
	{
		j = -1;
		while (++j < LA_RANK)
		{
			r.elms[i][j] = 0;
			k = -1;
			while (++k < LA_RANK)
			{
				r.elms[i][j] += a->elms[i][k] * b->elms[k][j];
			}
		}
	}
	return (r);
}

t_matr	*la_matr_mul_c(t_matr *m, double c)
{
	int	i;
	int	j;

	i = -1;
	while (++i < LA_RANK)
	{
		j = -1;
		while (++j < LA_RANK)
		{
			m->elms[i][j] *= c;
		}
	}
	return (m);
}
