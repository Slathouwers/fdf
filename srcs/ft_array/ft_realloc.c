/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:32:04 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/03 12:33:17 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

/*TO LIBFT!!*/
void	*ft_realloc(void *ptr, size_t new_size, size_t old_size)
{
	void	*ret;

	ret = malloc(new_size);
	if (ret)
		ft_memcpy(ret, ptr, old_size);
	free(ptr);
	return (ret);
}
