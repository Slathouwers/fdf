/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_transf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 10:01:30 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 10:21:44 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_vect	la_vect_transform(t_vect v, t_matr m)
{
	t_vect	r;

	r.x = m.elms[0][0] * v.x + m.elms[0][1] * v.y + m.elms[0][2] * v.z
		+ m.elms[0][3];
	r.y = m.elms[1][0] * v.x + m.elms[1][1] * v.y + m.elms[1][2] * v.z
		+ m.elms[1][3];
	r.z = m.elms[2][0] * v.x + m.elms[2][1] * v.y + m.elms[2][2] * v.z
		+ m.elms[2][3];
	return (r);
}

t_vect	la_vect_transform_div_w(t_vect v, t_matr m)
{
	t_vect	r;
	double	w;

	w = m.elms[3][0] * v.x + m.elms[3][1] * v.y + m.elms[3][2] * v.z
		+ m.elms[3][3];
	r.x = (
			m.elms[0][0] * v.x
			+ m.elms[0][1] * v.y
			+ m.elms[0][2] * v.z
			+ m.elms[0][3]) / w;
	r.y = (
			m.elms[1][0] * v.x
			+ m.elms[1][1] * v.y
			+ m.elms[1][2] * v.z
			+ m.elms[1][3]) / w;
	r.z = (
			m.elms[2][0] * v.x
			+ m.elms[2][1] * v.y
			+ m.elms[2][2] * v.z
			+ m.elms[2][3]) / w;
	return (r);
}
