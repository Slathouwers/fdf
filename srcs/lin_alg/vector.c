/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:29:35 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 12:55:22 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

double	la_vect_len(t_vect v)
{
	return (sqrt((v.x) * (v.x) + (v.y) * (v.y) + (v.z) * (v.z)));
}

t_vect	*la_vect_normalize(t_vect *v)
{
	double	len;

	len = la_vect_len(*v);
	if (len)
	{
		v->x /= len;
		v->y /= len;
		v->z /= len;
	}
	else
	{
		v->x = 0;
		v->y = 0;
		v->z = 1;
	}
	return (v);
}

void	la_vect_scale(t_vect *v, double c)
{
	v->x *= c;
	v->y *= c;
	v->z *= c;
}

t_vect	la_vect_scalar_mul(t_vect v, double s)
{
	t_vect	ret;

	ret.x = v.x * s;
	ret.y = v.y * s;
	ret.z = v.z * s;
	return (ret);
}

void	la_vect_decay(t_vect *v, double x)
{
	double	len;

	len = la_vect_len(*v);
	if (len <= x)
	{
		ft_bzero(v, sizeof(t_vect));
		return ;
	}
	*v = la_vect_scalar_mul(*v, (len - x) / len);
}
