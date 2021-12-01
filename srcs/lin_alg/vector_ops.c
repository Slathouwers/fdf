/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 09:54:17 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/01 09:58:45 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lin_alg.h"

t_vect	la_vect_add(t_vect v, t_vect w)
{
	v.x += w.x;
	v.y += w.y;
	v.z += w.z;
	return (v);
}

t_vect	la_vect_sub(t_vect v, t_vect w)
{
	v.x -= w.x;
	v.y -= w.y;
	v.z -= w.z;
	return (v);
}

double	la_vect_dot(t_vect v, t_vect w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

t_vect	la_vect_cross(t_vect v, t_vect w)
{
	t_vect	ret;

	ret.x = v.y * w.z - v.z * w.y;
	ret.y = v.z * w.x - v.x * w.z;
	ret.z = v.x * w.y - v.y * w.x;
	return (ret);
}
