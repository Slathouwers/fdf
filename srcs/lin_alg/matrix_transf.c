/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:55:25 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 12:54:11 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

void	la_matr_translate(t_matr *m, t_vect v)
{
	m->elms[0][3] += v.x;
	m->elms[1][3] += v.y;
	m->elms[2][3] += v.z;
}

void	la_matr_inv_translate(t_matr *m, t_vect v)
{
	m->elms[0][3] -= v.x;
	m->elms[1][3] -= v.y;
	m->elms[2][3] -= v.z;
}

/*https://ubm-twvideo01.s3.amazonaws.com/o1/vault/GDC2014/
Presentations/Melax_Stan_Math_For_Game.pdf*/
t_matr	la_matr_rotation(t_vect axis, double theta)
{
	t_matr	w;
	t_matr	w2;

	la_vect_normalize(&axis);
	ft_bzero(&w, sizeof(w));
	w.elms[0][0] = 0;
	w.elms[0][1] = -axis.z;
	w.elms[0][2] = axis.y;
	w.elms[1][0] = axis.z;
	w.elms[1][1] = 0;
	w.elms[1][2] = -axis.x;
	w.elms[2][0] = -axis.y;
	w.elms[2][1] = axis.x;
	w.elms[2][2] = 0;
	w.elms[3][3] = 1;
	w2 = la_matr_mul_ref(&w, &w);
	la_matr_mul_c(&w, sin(theta));
	la_matr_mul_c(&w2, 1 - cos(theta));
	w.elms[0][0] += 1.;
	w.elms[1][1] += 1.;
	w.elms[2][2] += 1.;
	la_matr_add_ref(&w, &w2);
	w.elms[3][3] = 1;
	return (w);
}

t_matr	la_matr_abitrary_rotation(t_vect axis, double theta, t_vect p)
{
	t_matr	m;
	t_matr	t;

	m = la_matr_rotation(axis, theta);
	la_matr_reset(&t);
	la_matr_translate(&t, p);
	m = la_matr_mul_ref(&t, &m);
	la_matr_reset(&t);
	la_matr_inv_translate(&t, p);
	m = la_matr_mul_ref(&m, &t);
	return (m);
}
