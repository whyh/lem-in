/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danial <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:39:36 by danial            #+#    #+#             */
/*   Updated: 2019/04/11 18:40:06 by danial           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_calculate_turns(t_lemin_data *data,
			t_lemin_solution *solution, unsigned int n_solution)
{
	unsigned int	i;

	i = 0;
	solution->turns = 0;
	while (i < solution->n_ways)
	{
		if (solution->turns < solution->ways[i].len - solution->ways[i].n_ants)
			solution->turns = solution->ways[i].len - solution->ways[i].n_ants;
		++i;
	}
	if (data->solutions[data->solution].turns > solution->turns)
		data->solution = n_solution;
	return (0);
}

int			lemin_solution(t_lemin_data *data)
{
	unsigned int	i;
	unsigned int	graph_width;

	if (data->graph[data->start].n_links < data->graph[data->end].n_links)
		graph_width = data->graph[data->start].n_links;
	else
		graph_width = data->graph[data->end].n_links;
	data->solution = 0;
	i = 0;
	while (i < LEMIN_MAX_SOLUTIONS)
	{
		if (!lemin_find_way(data, &data->solutions[i], graph_width) && i == 0)
		{
			ft_printf(LEMIN_ERR, LEMIN_ERR_NO_WAYS);
			return (0);
		}
		lemin_split_ants(data, &data->solutions[i]);
		static_calculate_turns(data, &data->solutions[i], i);
		if (data->solutions[data->solution].turns == 1)
			break ;
		++i;
	}
	return (1);
}
