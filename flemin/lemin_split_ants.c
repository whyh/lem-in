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

static unsigned int	static_best_way(t_lemin_solution *solution)
{
	unsigned int	min_time;
	unsigned int	way;
	unsigned int	i;

	min_time = solution->ways[0].len + solution->ways[0].n_ants;
	way = 0;
	i = 1;
	while (i < solution->n_ways)
	{
		if (solution->ways[i].len + solution->ways[i].n_ants < min_time)
		{
			min_time = solution->ways[i].len + solution->ways[i].n_ants;
			way = i;
		}
		++i;
	}
	solution->ways[way].n_ants++;
	return (way);
}

static int			static_exeption(t_lemin_data *data,
					t_lemin_solution *solution)
{
	unsigned int	way;
	unsigned int	ant;

	way = 0;
	while (way < solution->n_ways && solution->ways[way].len != 1)
		++way;
	if (way == solution->n_ways)
		return (0);
	ant = 0;
	while (ant < data->n_ants)
	{
		solution->ants[ant].n = ant + 1;
		solution->ants[ant].w = way;
		solution->ants[ant].pos = -1;
		++ant;
	}
	return (1);
}

void				lemin_split_ants(t_lemin_data *data,
					t_lemin_solution *solution)
{
	unsigned int	ant;

	solution->ants = ft_memalloc(sizeof(t_lemin_ant) * data->n_ants);
	if (static_exeption(data, solution))
		return ;
	ant = 0;
	while (ant < data->n_ants)
	{
		solution->ants[ant].n = ant + 1;
		solution->ants[ant].w = solution->n_ways;
		++ant;
	}
	ant = 0;
	while (ant < data->n_ants)
	{
		if (solution->ants[ant].w == solution->n_ways)
		{
			solution->ants[ant].w = static_best_way(solution);
			solution->ants[ant].pos = -1;
		}
		++ant;
	}
}
