/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_find_ways.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:36:45 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 15:01:15 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static unsigned int	static_shortest_way(t_lemin_data data, t_lemin_node *pos)
{
	unsigned int	i;
	unsigned int	nxt;

	nxt = pos->n_links;
	i = 0;
	while (pos->links && pos->links[i])
	{
		if (pos->links[i]->n != data.start
		&& pos->links[i]->w == 0
		&& pos->links[i]->value < pos->value
		&& (nxt == pos->n_links
		|| pos->links[i]->value < pos->links[nxt]->value))
			nxt = i;
		++i;
	}
	return (nxt);
}

static int	static_rm_room(t_lemin_data *data, t_lemin_way *way,
			t_lemin_node **ppos)
{
	way->path[way->len - 1] = 0;
	(*ppos)->w = LEMIN_BAD_WAY;
	if (way->len > 1)
		(*ppos) = &(data->graph[way->path[way->len - 2]]);
	else
		(*ppos) = &(data->graph[data->start]);
	way->len--;
	return (1);
}

static void	static_add_room(t_lemin_data *data, unsigned int way_n,
			t_lemin_node *nxt, t_lemin_node **ppos)
{
	t_lemin_way		*way;

	(*ppos) = nxt;
	way = &(data->ways[way_n]);
	if ((*ppos)->n != data->end)
		(*ppos)->w = way_n + 1;
	way->path[way->len] = (*ppos)->n;
	way->len++;
}

static int	static_compose_way(t_lemin_data *data, unsigned int way_n)
{
	t_lemin_node	*pos;
	t_lemin_way		*way;
	unsigned int	nxt;

	way = &(data->ways[way_n]);
	pos = &(data->graph[data->start]);
	way->path = ft_memalloc(sizeof(int) * data->n_links);
	way->n_ants = 0;
	way->len = 0;
	while (pos->n != data->end)
	{
		nxt = static_shortest_way(*data, pos);
		if (nxt == pos->n_links && way->len == 0)
		{
			ft_memdel((void**)(&way->path));
			return (0);
		}
		else if (nxt == pos->n_links)
			static_rm_room(data, way, &pos);
		else
			static_add_room(data, way_n, pos->links[nxt], &pos);
	}
	return (1);
}

int lemin_find_way(t_lemin_data *data)
{
	unsigned int	way_n;
	unsigned int	max_graph_width;

	max_graph_width = data->graph[data->end].n_links;
	data->ways = ft_memalloc(sizeof(t_lemin_way) * max_graph_width);
	way_n = 0;
	if (!lemin_set_way(data, way_n) || !lemin_set_value(data, data->end, 0))
		return (0);
	while (way_n < max_graph_width && static_compose_way(data, way_n))
	{
		if (!lemin_set_way(data, 1) || !lemin_set_value(data, data->end, 0))
			return (0);
		++way_n;
		if (data->ways[way_n - 1].len == 1)
			break ;
	}
	if (!data->ways[0].len)
	{
		ft_printf("[redError: %s\n", LEMIN_ERR_NO_WAYS);
		return (0);
	}
	data->n_ways = way_n;
	return (1);
}
