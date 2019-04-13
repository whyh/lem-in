/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_move_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:43:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/13 17:28:04 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		static_move_ant(t_lemin_data *data, t_lemin_vis *vis,
				unsigned int n_moved, t_lemin_ant *ant)
{
	t_lemin_way	*way;

	way = &(data->ways[ant->w]);
	if (ant->pos != -1)
		data->graph[way->path[ant->pos]].ant = 0;
	data->graph[way->path[ant->pos + 1]].ant = ant->n;
	if (!vis)
	{
		if (n_moved)
			ft_printf(" ");
		else
			ft_printf("\n");
		ft_printf("L%d-%s", ant->n, data->graph[way->path[ant->pos + 1]].name);
	}
	ant->pos++;
}

static void		static_store_pos(t_lemin_data *data, t_lemin_vis *vis,
				t_lemin_way *way, unsigned int ant)
{
	if (data->ants[ant].pos == -1)
	{
		vis->ant_posx[ant] = data->graph[data->start].x;
		vis->ant_posy[ant] = data->graph[data->start].y;
	}
	else
	{
		vis->ant_posx[ant] = data->graph[way->path[data->ants[ant].pos]].x;
		vis->ant_posy[ant] = data->graph[way->path[data->ants[ant].pos]].y;
	}
}

int				lemin_move_ants_turn(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	ant;
	unsigned int	n_moved;
	t_lemin_way		*way;

	n_moved = 0;
	ant = 0;
	while (ant < data->n_ants)
	{
		way = &(data->ways[data->ants[ant].w]);
		if (vis)
			static_store_pos(data, vis, way, ant);
		if (data->ants[ant].pos < (int)way->len - 1
		&& (data->ants[ant].pos == (int)way->len - 2
		|| data->graph[way->path[data->ants[ant].pos + 1]].ant == 0))
		{
			static_move_ant(data, vis, n_moved, &(data->ants[ant]));
			++n_moved;
		}
		++ant;
	}
	return (n_moved);
}

void			lemin_move_ants(t_lemin_data *data)
{
	unsigned int	n_moved;

	n_moved = (UI)lemin_move_ants_turn(data, NULL);
	while (n_moved != 0)
		n_moved = (UI)lemin_move_ants_turn(data, NULL);
	ft_printf("\n");
}
