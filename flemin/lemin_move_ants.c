/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_move_ants.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 14:43:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/01 21:40:35 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

//TODO rewrite

//int		lemin_move_ants(t_lemin_data *data)
//{
//	unsigned int	i;
//	unsigned int	n_moved;
//
//	n_moved = 1;
//	while (n_moved != 0)
//	{
//		n_moved = 0;
//		i = 0;
//		while (i < data->n_ants)
//		{
//			if (data->ants[i].pos < (int)data->ways[data->ants[i].w].len - 1
//			&& (data->ants[i].pos == (int)data->ways[data->ants[i].w].len - 2
//			|| data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos + 1]].ant == 0))
//			{
//				if (data->ants[i].pos != -1)
//					data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos]].ant = 0;
//				data->ants[i].pos++;
//				data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos]].ant = data->ants[i].n;
//				if (n_moved == 0)
//					ft_printf("\n");
//				else
//					ft_printf(" ");
//				ft_printf("L%d-%s", data->ants[i].n,
//						data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos]].name);
//				n_moved++;
//			}
//			++i;
//		}
//	}
//	ft_printf("\n");
//	return (n_moved);
//}



////////////



int		lemin_move_ants(t_lemin_data *data)
{
	unsigned int	i;
	unsigned int	ant;
	unsigned int	pos;
	unsigned int	n_moved;

	n_moved = 1;
	while (n_moved != 0)
	{
		n_moved = 0;
		i = 0;
		while (i < data->n_ways)
		{
			pos = data->ways[i].len - 1;
			while (data->ways[i].n_ants && pos > 0)
			{
				if (data->graph[data->ways[i].path[pos - 1]].ant)
				{
					data->graph[data->ways[i].path[pos]].ant = data->graph[data->ways[i].path[pos - 1]].ant;
					data->graph[data->ways[i].path[pos - 1]].ant = 0;
					data->ants[data->graph[data->ways[i].path[pos]].ant].pos++;
					if (pos == data->ways[i].len - 1)
						data->ways[i].n_ants--;
					if (n_moved == 0)
						ft_printf("\n");
					else
						ft_printf(" ");
					ft_printf("L%d-%s", data->graph[data->ways[i].path[pos]].ant, data->graph[data->ways[i].path[pos]].name);
					n_moved++;
				}
				--pos;
			}
			ant = 0;
			while (ant < data->n_ants)
			{
				if (data->ants[ant].w == i && data->ants[ant].pos == -1)
				{
					data->ants[ant].pos++;
					data->graph[data->ways[i].path[0]].ant = data->ants[ant].n;
					if (n_moved == 0)
						ft_printf("\n");
					else
						ft_printf(" ");
					ft_printf("L%d-%s", data->ants[ant].n, data->graph[data->ways[i].path[pos]].name);
					n_moved++;
					break ;
				}
				++ant;
			}
			++i;
		}
	}
	ft_printf("\n");
	return (n_moved);
}

