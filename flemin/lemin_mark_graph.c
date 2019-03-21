/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mark_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:51:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/21 17:34:57 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		lemin_mark_graph(t_lemin_data *data, unsigned int room,
		unsigned int value)
{
	unsigned int	i;
	t_lemin_node	*graph;

	graph = data->graph;
	if (value == LEMIN_MAX_VALUE + 1)
	{
		ft_printf("Error");
		return (0);
	}
	graph[room].value = value;
	i = 0;
	while (graph[room].links[i])
	{
		if (graph[room].links[i]->w == 0
		&& (graph[room].links[i]->value == LEMIN_MAX_VALUE + 1
		|| graph[room].links[i]->value > graph[room].value))
			if (!lemin_mark_graph(data, graph[room].links[i]->n, value + 1))
				return (0);
		++i;
	}
	return (1);
}

void	lemin_set_w(t_lemin_data *data, unsigned int re)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_nodes)
	{
		if (!re || data->graph[i].w == LEMIN_MAX_WAYS + 1)
			data->graph[i].w = 0;
		++i;
	}
}

static unsigned int	static_shortest_way(t_lemin_data data, t_lemin_node *pos)
{
	unsigned int	i;
	unsigned int	nxt;

	i = 0;
	nxt = pos->n_links;
	while (pos->links && pos->links[i])
	{
		if (pos->links[i]->w == 0
		&& (pos->n == data.start || pos->links[i]->value <= pos->value)
		&& (nxt == pos->n_links || pos->links[i]->value < pos->links[nxt]->value))
			nxt = i;
		++i;
	}
	return (nxt);
}
//
//static unsigned int	static_first_way(t_lemin_data data, t_lemin_node *pos)
//{
//	unsigned int	i;
//
//	i = 0;
//	while (pos->links && pos->links[i])
//	{
//		if (pos->links[i]->w == 0
//		&& (pos->n == data.start || pos->links[i]->value <= pos->value))
//			return (i);
//		++i;
//	}
//	return (pos->n_links);
//}

int		lemin_way(t_lemin_data *data, unsigned int w)
{
	t_lemin_node	*pos;
	unsigned int	nxt;

	pos = &(data->graph[data->start]);
	data->ways[w].path = ft_memalloc(sizeof(int) * data->n_links);
	data->ways[w].n_ants = 0;
	data->ways[w].len = 0;
	while (pos != &(data->graph[data->end]))
	{
		if ((nxt = static_shortest_way(*data, pos)) == pos->n_links)
		{
			if (data->ways[w].len == 0)
			{
				ft_memdel((void**)(&(data->ways[w].path)));
				data->ways[w].len = 0;
				return (0);
			}
			data->ways[w].path[data->ways[w].len - 1] = 0;
			pos->w = LEMIN_MAX_WAYS + 1;
			if ((int)(data->ways[w].len) - 2 >= 0)
				pos = &(data->graph[data->ways[w].path[data->ways[w].len - 2]]);
			else
				pos = &(data->graph[data->start]);
			data->ways[w].len--;
		}
		else
		{
			pos = pos->links[nxt];
			if (pos->n != data->end)
				pos->w = w + 1;
			data->ways[w].path[data->ways[w].len] = pos->n;
			data->ways[w].len++;
		}
	}
	return (1);
}

int lemin_get_way(t_lemin_data *data)
{
	unsigned int	i;

	data->ways = ft_memalloc(sizeof(t_lemin_way) * data->graph[data->end].n_links);
	lemin_set_w(data, 0);
	lemin_mark_graph(data, data->end, 0);
	i = 0;
	while (i < data->graph[data->end].n_links && lemin_way(data, i))
	{
		lemin_set_w(data, 1);
		lemin_mark_graph(data, data->end, 0);
		++i;
		if (data->ways[i - 1].len == 1)
			break;
	}
	if (!data->ways[0].len)
	{
		ft_printf("[redError: now way was found\n");
		return (0);
	}
	data->n_ways = i;
	return (1);
}
