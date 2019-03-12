/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:13:38 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 12:59:48 by dderevyn         ###   ########.fr      ё */
/* ************************************************************************** */

#include "lemin.h"

//void	lemin_cut_deadend(t_lemin_data *data, int value, int node)
//{
//	int	i;
//
//	if ()
//	{
//		;
//	}
//	i = 0;
//	while ((i = lemin_find_value(data, value, i)) > 0)
//	{
//		;
//	}
//}
//
//void	lemin_move_ant(t_lemin_data *data, int from, int to)
//{
//	ft_printf("");
//
//}
//
//void	lemin_execute(t_lemin_data *data)
//{
//	int i;
//	int n;
//
//	while (data->graph[data->end].ants != data->ants)
//	{
//		i = 0;
//		while (i < data->n_ways)
//		{
//			n = 0;
//			while (n < data->ways[i].len)
//			{
//				if (data->graph[data->ways[i].path[n]].ants == 1)
//					lemin_move_ant(data, from, to);
//				++n;
//			}
//
//			++i;
//		}
//	}
//}

int main(int argc, char **argv)
{
	t_lemin_data	data;
	int 			i;

	(void)argv;
	(void)argc;
	if (!lemin_parse(&data))
	{
		ft_printf("[greenUsage:~] %s[cyan%s", "./lem-in\n",
		"1\n##start\n0 250 250\n2 260 350\n3 560 450\n##end\n1 750 750\n0-2\n");
		return (0);//TODO write usage
	}
	lemin_mark_graph(&data, data.node - 1, 0);
//	lemin_cut_deadend(&data, 1, data.node - 1);
//	lemin_path_generator();
//	lemin_execute();
	i = 0;
	while (i <= data.node)
	{
//		ft_printf("%s", data.graph[i].name);
		ft_printf("%d\n", data.graph[i].value);
//		ft_printf(" %d ", data.graph[i].x);
//		ft_printf("%d\n\n", data.graph[i].y);
		++i;
	}
	//if value > else if value ==
	return (1);
}
