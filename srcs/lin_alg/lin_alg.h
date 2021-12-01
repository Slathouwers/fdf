/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lin_alg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:20:20 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 12:54:08 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIN_ALG_H
# define LIN_ALG_H

# include <math.h>
# include "../libs/libftprintf/includes/ft_printf_bonus.h"

# define LA_RANK 4

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}	t_vect;

typedef struct s_matr
{
	double	elms[LA_RANK][LA_RANK];
}	t_matr;

/*VECTOR*/
double	la_vect_len(t_vect v);
t_vect	*la_vect_normalize(t_vect *v);
void	la_vect_scale(t_vect *v, double c);
t_vect	la_vect_scalar_mul(t_vect v, double s);
void	la_vect_decay(t_vect *v, double x);

/*VECTOR OPERATIONS*/
t_vect	la_vect_add(t_vect v, t_vect w);
t_vect	la_vect_sub(t_vect v, t_vect w);
double	la_vect_dot(t_vect v, t_vect w);
t_vect	la_vect_cross(t_vect v, t_vect w);

/*VECTOR TRANSFORMATIONS*/
t_vect	la_vect_transform(t_vect v, t_matr m);
t_vect	la_vect_transform_w(t_vect v, t_matr m);

/*MATRIX*/
t_matr	la_matr_identity(void);
t_matr	*la_matr_reset(t_matr *m);

/*MATRIX OPERATIONS*/
t_matr	*la_matr_add_ref(t_matr *a, t_matr *b);
t_matr	la_matr_mul(t_matr a, t_matr b);
t_matr	la_matr_mul_ref(t_matr *a, t_matr *b);
t_matr	*la_matr_mul_c(t_matr *m, double c);

/*MATRIX TRANSFORMATIONS*/
void	la_matr_translate(t_matr *m, t_vect v);
void	la_matr_inv_translate(t_matr *m, t_vect v);
t_matr	la_matr_rotation(t_vect axis, double theta);
t_matr	la_matr_abitrary_rotation(t_vect axis, double theta, t_vect p);

#endif