/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_mark_graph.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 20:51:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 20:58:58 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_mark_graph(t_lemin_data *data, int n, int value)
{
	int i;
	int n_tmp;

	i = 0;
	data->graph[n].value = value;
	while (i <= data->link)
	{
		if (ft_strncmp(data->link0[i], data->graph[n].name, -1))
		{
			n_tmp = lemin_find_node(data, data->link1[i], 0);
			if (data->graph[n_tmp].value == -1
			|| data->graph[n_tmp].value > value)
				lemin_mark_graph(data, n_tmp, value + 1);
		}
		else if (ft_strncmp(data->link1[i], data->graph[n].name, -1))
		{
			n_tmp = lemin_find_node(data, data->link0[i], 0);
			if (data->graph[n_tmp].value == -1
			|| data->graph[n_tmp].value > value)
				lemin_mark_graph(data, n_tmp, value + 1);
		}
		++i;
	}
}
