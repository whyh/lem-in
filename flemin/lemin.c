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

void	lemin_print(t_lemin_data data, int y)
{
	int i;
	int n;

	i = 0;
	while (i < data.n_nodes)
	{
		ft_printf("%s %d %d\n", data.graph[i].name, data.graph[i].x, data.graph[i].y);
		ft_printf("value %d  |  way %d  |  ants %d\n", data.graph[i].value, data.graph[i].w, data.graph[i].n_ants);
		n = 0;
		while (n < data.graph[i].n_links)
		{
			ft_printf("%s ", data.graph[i].links[n]->name);
			++n;
		}
		ft_printf("\n\n");
		++i;
	}
	i  = 0;
	while (i < y - 1)
	{
		n = 0;
		while (n < data.ways[i].len)
		{
			ft_printf("%s ", data.graph[data.ways[i].path[n]].name);
			++n;
		}
		ft_printf("   |   len %d   |   ants %d\n", data.ways[i].len, data.ways[i].ants);
		++i;
	}
}

void lemin_split_ants(t_lemin_data *data, int i)
{
	int n;
	int t;
	int min;
	int min_n;

	t = 0;
	while (t < data->ants)
	{
		n = 0;
		min = data->ways[0].len + data->ways[0].ants;
		min_n = 0;
		while (data->ways[n].len && n < i)
		{
			if (data->ways[n].len + data->ways[n].ants < min)
			{
				min = data->ways[n].len + data->ways[n].ants;
				min_n = n;
			}
			++n;
		}
		data->ants_arr[t].n = t;
		data->ants_arr[t].w = min_n;
		data->ants_arr[t].pos = 0;
		data->ways[min_n].ants++;
		++t;
	}
}

void	lemin_move_ant(t_lemin_data *data, int w, int pos)
{
	int i;

	i = 0;
	while (i < data->ants)
	{
		if (data->ants_arr[i].w == w && data->ants_arr[i].pos == pos - 1)
		{
			if (data->ways[w].len - 1 == pos)
				data->graph[data->end].n_ants++;
			data->ants_arr[i].pos++;
			ft_printf("L%d-%s ", data->ants_arr[i].n + 1, data->graph[data->ways[data->ants_arr[i].w].path[data->ants_arr[i].pos]]);
			data->ways[w].p_ant[pos] = 1;
			data->ways[w].p_ant[pos - 1] = 0;
			return ;
		}
		++i;
	}
}

void	lemin_exec(t_lemin_data *data)
{
	int t;
	int i;

	while (data->graph[data->end].n_ants != data->ants)
	{
		i = 0;
		while (data->ways[i].len)
		{
			t = data->ways[i].len - 1;
			while (t > 0)
			{
				if (data->ways[i].p_ant[t] == 0 || t == data->ways[i].len - 1)
				{
					lemin_move_ant(data, i, t);
					//if moved change p_ant[i] to 0 and where moved to 1
				}
				--t;
			}
			++i;
		}
		ft_printf("\n");
	}
}

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
	lemin_mark_graph(&data, data.end, 0);
	i = 1;
	data.graph[data.start].n_ants = (int)data.ants;
	data.ways = ft_memalloc(sizeof(t_lemin_way) * data.ants);
	while (i < data.ants && lemin_way(&data, i - 1))
	{
		lemin_reset_w(&data);
		lemin_mark_graph(&data, data.end, 0);
		++i;
	}
//	if (!data.ways[0].len)
//	{
//		ft_printf("[redError: now way from start to end was found\n");
//		return (0);
//	}
//	data.ants_arr = ft_memalloc(sizeof(t_lemin_ant) * data.ants);
//	lemin_split_ants(&data, i);
//	ft_printf("%s\n", data.input);
//	lemin_exec(&data);
	lemin_print(data, i);
	return (1);
}
