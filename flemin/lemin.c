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
//
//void	lemin_print(t_lemin_data data, int y)
//{
//	unsigned int i;
//	unsigned int n;
//
//	i = 0;
//	while (i < data.n_nodes)
//	{
//		ft_printf("%s %d %d\n", data.graph[i].name, data.graph[i].x, data.graph[i].y);
//		ft_printf("value %d  |  way %d \n", data.graph[i].value, data.graph[i].w);
//		n = 0;
//		while (n < data.graph[i].n_links)
//		{
//			ft_printf("%s ", data.graph[i].links[n]->name);
//			++n;
//		}
//		ft_printf("\n\n");
//		++i;
//	}
//	i  = 0;
//	while (i < y - 1)
//	{
//		n = 0;
//		while (n < data.ways[i].len)
//		{
//			ft_printf("%s ", data.graph[data.ways[i].path[n]].name);
//			++n;
//		}
//		ft_printf("   |   len %d   |   ants %d\n", data.ways[i].len, data.ways[i].n_ants);
//		++i;
//	}
//}

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

void lemin_split_ants(t_lemin_data *data)
{
	unsigned int	i;

	i = 0;
	data->ants = ft_memalloc(sizeof(t_lemin_ant) * data->n_ants);
	while (i < data->n_ants)
	{
		data->ants[i].n = i + 1;
		data->ants[i].w = data->n_ways;
		++i;
	}
	i = 0;
	while (i < data->n_ants)
	{
		if (data->ants[i].w == data->n_ways)
		{
			data->ants[i].w = static_best_way(data);
			data->ants[i].pos = -1;
		}
		++i;
	}
}

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

int main(int argc, char **argv)
{
	t_lemin_data	data;

	(void)argv;
	(void)argc;
	if (!lemin_parse(&data))
	{
		ft_printf("[greenUsage:~] %s[cyan%s", "./lem-in\n",
		"1\n##start\n0 250 250\n2 260 350\n3 560 450\n##end\n1 750 750\n0-2\n");
		return (0);//TODO write usage
	}
	if (!lemin_get_way(&data))
	{
		//TODO free everything
		return (0);
	}
//	ft_printf("%s", data.input);
	lemin_split_ants(&data);
	lemin_move_ants(&data);
//	lemin_print(data, i);
	return (1);
}
