/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_move_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:43:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/04 15:40:32 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			static_move_ant(t_lemin_node **graph, t_lemin_way *way,
					unsigned int n_moved, t_lemin_ant *ant)
{
	if (ant->pos != -1)
		(*graph)[way->path[ant->pos]].ant = 0;
	(*graph)[way->path[ant->pos + 1]].ant = ant->n;
	if (n_moved)
		ft_printf(" ");
	else
		ft_printf("\n");
	ft_printf("L%d-%s", ant->n, (*graph)[way->path[ant->pos + 1]].name);
	ant->pos++;
}

static unsigned int	static_turn(t_lemin_data *data)
{
	unsigned int	i;
	unsigned int	n_moved;
	t_lemin_way		*way;

	n_moved = 0;
	i = 0;
	while (i < data->n_ants)
	{
		way = &(data->ways[data->ants[i].w]);
		if (data->ants[i].pos < (int)way->len - 1
		&& (data->ants[i].pos == (int)way->len - 2
		|| data->graph[way->path[data->ants[i].pos + 1]].ant == 0))
		{
			static_move_ant(&data->graph, way, n_moved, &(data->ants[i]));
			++n_moved;
		}
		++i;
	}
	return (n_moved);
}

void	lemin_move_ants(t_lemin_data *data)
{
	unsigned int	n_moved;

	n_moved = static_turn(data);
	while (n_moved != 0)
		n_moved = static_turn(data);
	ft_printf("\n");
}
