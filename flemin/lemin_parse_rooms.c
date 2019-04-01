/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:52:24 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 21:09:36 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_prop(t_lemin_data *data, int room)
{
	int	tmp_room;

	tmp_room = 0;
	while (tmp_room < room)
	{
		if (ft_strncmp(data->graph[tmp_room].name, data->graph[room].name, -1)
		|| (data->graph[tmp_room].x == data->graph[room].x
		&& data->graph[tmp_room].y == data->graph[room].y))
		{
			ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM2);
			return (0);
		}
		++tmp_room;
	}
	return (1);
}

static int	static_coord(t_lemin_parse *parse, int *coord)
{
	long long	tmp;

	tmp = ft_atoibase(DEC, &(parse->buff[parse->i]));
	if (tmp > INT_MAX || tmp < INT_MIN)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM3);
		return (0);
	}
	*coord = (int)tmp;
	if (ft_strin(SIGNS, parse->buff[parse->i]))
		parse->i++;
	while (ft_strin(DEC, parse->buff[parse->i]))
		parse->i++;
	parse->i++;
	return (1);
}

static int	static_start_end(t_lemin_parse *parse)
{
	if (!parse->start || parse->start_next)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_START2);
		return (0);
	}
	else if (!parse->end || parse->end_next)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_END2);
		return (0);
	}
	return (1);
}

int			lemin_parse_rooms(t_lemin_data *data, t_lemin_parse *parse,
			char *input)
{
	unsigned int	room;
	unsigned int	tmp_i;

	if (!static_start_end(parse))
		return (0);
	data->graph = ft_memalloc(sizeof(t_lemin_data) * data->n_nodes);
	room = 0;
	while (room < data->n_nodes)
	{
		tmp_i = (int)ft_strchr_i(&(input[parse->i]), ' ');
		data->graph[room].name = ft_strndup(&(input[parse->i]), tmp_i);
		data->graph[room].value = LEMIN_MAX_VALUE + 1;
		data->graph[room].n = room;
		data->graph[room].w = 0;
		data->graph[room].n_links = 0;
		data->graph[room].links = NULL;
		parse->i += tmp_i + 1;
		if (!static_coord(parse, &(data->graph[room].x))
		|| !static_coord(parse, &(data->graph[room].y))
		|| !static_valid_prop(data, room))
			return (0);
		++room;
	}
	parse->valid_rooms = 1;
	return (1);
}
