/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_find_ways.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:36:45 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/03 20:33:04 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static unsigned int	static_next_room(t_lemin_data data, t_lemin_room *pos)
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

static int			static_compose_way(t_lemin_data *data,
					t_lemin_solution *solution, unsigned int way_n)
{
	t_lemin_room	*pos;
	t_lemin_way		*way;
	unsigned int	nxt;

	if (data->graph[data->start].value == LEMIN_INIT_VALUE)
		return (0);
	way = &(solution->ways[way_n]);
	pos = &(data->graph[data->start]);
	way->path = ft_memalloc(sizeof(int) * data->n_links);
	way->n_ants = 0;
	way->len = 0;
	while (pos->n != data->end)
	{
		nxt = static_next_room(*data, pos);
		pos = pos->links[nxt];
		way = &(solution->ways[way_n]);
		if (pos->n != data->end)
			pos->w = way_n + 1;
		way->path[way->len] = pos->n;
		way->len++;
	}
	return (1);
}

int					lemin_find_way(t_lemin_data *data,
					t_lemin_solution *solution, unsigned int graph_width)
{
	unsigned int	way_n;

	solution->ways = ft_memalloc(sizeof(t_lemin_way) * graph_width);
	way_n = 0;
	if (!lemin_set_way(data, way_n) || !lemin_set_value(data, data->end, 0))
		return (0);
	while (way_n < graph_width && static_compose_way(data, solution, way_n))
	{
		if (!lemin_set_way(data, 1) || !lemin_set_value(data, data->end, 0))
			return (0);
		++way_n;
		if (solution->ways[way_n - 1].len == 1)
			break ;
	}
	if (!solution->ways[0].len)
		return (0);
	solution->n_ways = way_n;
	return (1);
}
