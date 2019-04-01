/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:52:24 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/01 19:32:39 by dderevyn         ###   ########.fr       */
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

static int	static_coord(t_lemin_parse *parse, char *input, int *coord)
{
	long long	tmp;

	tmp = ft_atoibase(DEC, &(input[parse->i]));
	if (tmp > INT_MAX || tmp < INT_MIN)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM3);
		return (0);
	}
	*coord = (int)tmp;
	if (ft_strin(SIGNS, input[parse->i]))
		parse->i++;
	while (ft_strin(DEC, input[parse->i]))
		parse->i++;
	parse->i++;
	return (1);
}

static int	static_check_n_alloc(t_lemin_data *data, t_lemin_parse *parse)
{
	unsigned int	room;

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
	data->graph = ft_memalloc(sizeof(t_lemin_data) * data->n_nodes);
	room = 0;
	while (room < data->n_nodes)
	{
		data->graph[room].name = NULL;
		++room;
	}
	return (1);
}

static void	static_fill_inf(t_lemin_node *room, unsigned int n)
{
	room->n = n;
	room->value = LEMIN_MAX_VALUE + 1;
	room->w = 0;
	room->n_links = 0;
	room->links = NULL;
	room->ant = 0;
}

int			lemin_parse_rooms(t_lemin_data *data, t_lemin_parse *parse,
			char *input)
{
	unsigned int	tmp_i;
	unsigned int	room;

	if (!static_check_n_alloc(data, parse))
		return (0);
	room = 0;
	while (room < data->n_nodes)
	{
		while (input[parse->i] == '#')
			parse->i += ft_strchr_i(&(input[parse->i]), '\n') + 1;
		tmp_i = (int)ft_strchr_i(&(input[parse->i]), ' ');
		data->graph[room].name = ft_strndup(&(input[parse->i]), tmp_i);
		static_fill_inf(&data->graph[room], room);
		parse->i += tmp_i + 1;
		if (!static_coord(parse, input, &(data->graph[room].x))
		|| !static_coord(parse, input, &(data->graph[room].y))
		|| !static_valid_prop(data, room))
			return (0);
		++room;
	}
	parse->rooms = 1;
	return (1);
}
