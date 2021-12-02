/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 09:14:11 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/02 09:17:06 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	terminate(char *err_message)
{
	if (errno == 0)
		ft_putendl_fd(err_message, 2);
	else
		perror(err_message);
	exit(EXIT_FAILURE);
}

int	get_index(int x, int y, int width)
{
	return (y * width + x);
}

double	radians(double degrees)
{
	return (degrees * M_PI / 180.0);
}

/*PUT IN LIBFT!!*/
int	ft_isint(const char *str)
{
	int			sign;
	int			i;
	long long	num;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return ((num * sign) <= 2147483647 && (num * sign) >= -2147483648);
}

int	ft_abs(int v)
{
	if (v < 0)
		return (-v);
	return (v);
}
