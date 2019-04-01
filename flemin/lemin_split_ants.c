/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_split_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:41:16 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 14:43:43 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static unsigned int static_best_way(t_lemin_data *data)
{
	unsigned int	min_time;
	unsigned int	way;
	unsigned int	i;

	min_time = data->ways[0].len + data->ways[0].n_ants;
	way = 0;
	i = 1;
	while (i < data->n_ways)
	{
		if (data->ways[i].len + data->ways[i].n_ants < min_time)
		{
			min_time = data->ways[i].len + data->ways[i].n_ants;
			way = i;
		}
		++i;
	}
	data->ways[way].n_ants++;
	return (way);
}

static int	static_exeption(t_lemin_data *data)
{
	unsigned int	way;
	unsigned int	ant;

	way = 0;
	while (way < data->n_ways && data->ways[way].len != 1)
		++way;
	if (way == data->n_ways)
		return (0);
	ant = 0;
	while (ant < data->n_ants)
	{
		data->ants[ant].n = ant + 1;
		data->ants[ant].w = way;
		data->ants[ant].pos = -1;
		++ant;
	}
	return (1);
}

void lemin_split_ants(t_lemin_data *data)
{
	unsigned int	ant;

	data->ants = ft_memalloc(sizeof(t_lemin_ant) * data->n_ants);
	if (static_exeption(data))
		return ;
	ant = 0;
	while (ant < data->n_ants)
	{
		data->ants[ant].n = ant + 1;
		data->ants[ant].w = data->n_ways;
		++ant;
	}
	ant = 0;
	while (ant < data->n_ants)
	{
		if (data->ants[ant].w == data->n_ways)
		{
			data->ants[ant].w = static_best_way(data);
			data->ants[ant].pos = -1;
		}
		++ant;
	}
}
