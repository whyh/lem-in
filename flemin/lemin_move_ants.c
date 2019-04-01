/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_move_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:43:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 16:45:14 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//TODO rewrite

static int	static_not_occupied(t_lemin_ant *ants, unsigned int n_ants,
			unsigned int w, unsigned int pos)
{
	unsigned int	i;

	i = 0;
	while (i < n_ants)
	{
		if (ants[i].w == w && ants[i].pos == (int)pos)
			return (0);
		++i;
	}
	return (1);
}

int		lemin_move_ants(t_lemin_data *data)
{
	unsigned int	i;
	unsigned int	n_moved;

	n_moved = 1;
	while (n_moved != 0)
	{
		n_moved = 0;
		i = 0;
		while (i < data->n_ants)
		{
			if (data->ants[i].pos < (int)data->ways[data->ants[i].w].len - 1
			&& (data->ants[i].pos == (int)data->ways[data->ants[i].w].len - 2
			|| static_not_occupied(data->ants, data->n_ants, data->ants[i].w , (UI)(data->ants[i].pos + 1))))
			{
				data->ants[i].pos++;
				if (n_moved == 0)
					ft_printf("\n");
				else
					ft_printf(" ");
				ft_printf("L%d-%s", data->ants[i].n,
						  data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos]].name);
				n_moved++;
			}
			++i;
		}
	}
	ft_printf("\n");
	return (n_moved);
}
