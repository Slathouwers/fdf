/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 07:06:59 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 14:52:33 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	set_z_minmax(t_map *model)
{
	size_t		i;
	size_t		arr_size;

	arr_size = model->width * model->height;
	i = -1;
	model->z_max = -2147483648;
	model->z_min = 2147483647;
	while (++i < arr_size)
	{
		if (model->z_data[i] > model->z_max)
			model->z_max = model->z_data[i];
		if (model->z_data[i] < model->z_min)
			model->z_min = model->z_data[i];
	}
	model->dz = model->z_max - model->z_min;
}

static int	get_z_val(char *s)
{
	int	i;

	if (!ft_isint(s))
		ft_terminate("Map ERROR: Non integer value found!");
	i = ft_atoi(s);
	return (i);
}

static void	parse_split(char **split, t_map *model)
{
	int	width;

	width = 0;
	while (*split)
	{
		ft_int_array_add(&model->z_arr, get_z_val(*split));
		width++;
		split++;
	}
	if (!model->height)
		model->width = width;
	else if (model->width != width)
		ft_terminate("Map ERROR: line length inconsiteny!");
}

int	parse_map(t_map *model, int fd)
{
	char	*line;
	char	**line_split;

	ft_int_array_init(&model->z_arr);
	line = get_next_line(fd);
	while (line)
	{
		line_split = ft_split(line, ' ');
		if (!line_split)
			ft_terminate("Map ERROR: Memory insufficient!");
		parse_split(line_split, model);
		ft_free_split(line_split);
		free(line);
		line = get_next_line(fd);
		model->height++;
	}
	if (!model->z_arr.count)
		return (0);
	model->z_data = model->z_arr.data;
	set_z_minmax(model);
	return (1);
}
