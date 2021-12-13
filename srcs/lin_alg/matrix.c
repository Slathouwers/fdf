/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:25:44 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 14:19:24 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_matr	la_matr_identity(void)
{
	t_matr	m;

	la_matr_reset(&m);
	return (m);
}

t_matr	*la_matr_reset(t_matr *m)
{
	int	i;

	ft_bzero(m, sizeof(*m));
	i = -1;
	while (++i < LA_RANK)
		m->elms[i][i] = 1;
	return (m);
}
/*
https://stackoverflow.com/questions/2937702/
	i-want-to-find-determinant-of-4x4-matrix-in-c-sharp */