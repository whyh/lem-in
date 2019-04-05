/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mark_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:51:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 14:37:54 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	lemin_set_value(t_lemin_data *data, unsigned int room, unsigned int value)
{
	unsigned int	i;
	t_lemin_node	*graph;

	if (value > LEMIN_MAX_VALUE)
	{
		ft_printf("[redError: %s\n", LEMIN_ERR_BIG_GRAPH);
		return (0);
	}
	graph = data->graph;
	graph[room].value = value;
	if (room == data->start)
		return (1);
	i = 0;
	while (graph[room].links[i])
	{
		if (graph[room].links[i]->w == 0
		&& (graph[room].links[i]->value == LEMIN_INIT_VALUE
		|| graph[room].links[i]->value > graph[room].value))
			if (!lemin_set_value(data, graph[room].links[i]->n, value + 1))
				return (0);
		++i;
	}
	return (1);
}

int	lemin_set_way(t_lemin_data *data, unsigned int way_n)
{
	unsigned int	room;

	room = 0;
	while (room < data->n_nodes)
	{
		if (way_n == 0 || data->graph[room].w == LEMIN_BAD_WAY)
			data->graph[room].w = 0;
		data->graph[room].value = LEMIN_INIT_VALUE;
		++room;
	}
	return (1);
}
