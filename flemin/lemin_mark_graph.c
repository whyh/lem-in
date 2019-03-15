/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mark_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:51:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/15 17:45:10 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_mark_graph(t_lemin_data *data, int n, int value)
{
	int i;

	i = 0;
	if (data->graph[n].w == 0)
		data->graph[n].value = value;
	while (data->graph[n].links[i])
	{
		if (data->graph[n].links[i]->w == 0
		&& (data->graph[n].links[i]->value == -1
		|| data->graph[n].links[i]->value > data->graph[n].value))
			lemin_mark_graph(data, data->graph[n].links[i]->n, value + 1);
		++i;
	}
}

void	lemin_reset_w(t_lemin_data *data)
{
	int i;

	i = 0;
	while (i < data->n_nodes)
	{
		if (data->graph[i].w == -1 || i == data->end || i == data->start)
			data->graph[i].w = 0;
		++i;
	}
}

int		lemin_way(t_lemin_data *data, int w)
{
	t_lemin_node	*curr;
	int 			i;
	int 			t;

	t = 0;
	data->ways[w].path = ft_memalloc(sizeof(int) * data->n_links);
	data->ways[w].p_ant = ft_memalloc(sizeof(int) * data->n_links);
	data->ways[w].ants = 0;
	curr = &(data->graph[data->start]);
	curr->w = w + 1;
	data->ways[w].path[0] = curr->n;
	data->ways[w].len = 1;
	while (curr != &(data->graph[data->end]))
	{
		t++;
		i = 0;
		while (curr->links && curr->links[i]
		&& (curr->links[i]->value >= curr->value || curr->links[i]->w != 0))
			++i;
		if (!curr->links || !curr->links[i])
		{
			i = 0;
			while (curr->links && curr->links[i] && (curr->links[i] == &(data->graph[data->start])
			|| curr->links[i]->value != curr->value || curr->links[i]->w != 0))
				++i;
		}
		if (!curr->links || !curr->links[i])
		{
			if (data->ways[w].len == 1)
			{
				ft_memdel((void**)(&(data->ways[w].path)));
				data->ways[w].len = 0;
				return (0);
			}
			data->ways[w].len--;
			data->ways[w].path[data->ways[w].len] = 0;
			curr->w = -1;
			curr = &(data->graph[data->ways[w].path[data->ways[w].len - 1]]);
		}
		else
		{
			curr = curr->links[i];
			data->ways[w].path[data->ways[w].len] = curr->n;
			curr->w = w;
			data->ways[w].len++;
		}
	}
	return (1);
}
