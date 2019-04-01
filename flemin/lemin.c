/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:13:38 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 12:59:48 by dderevyn         ###   ########.fr       */
/* ************************************************************************** */

#include "lemin.h"

//void	lemin_print(t_lemin_data data)
//{
//	unsigned int i;
//	unsigned int n;
//
//	i = 0;
//	while (i < data.n_nodes && i < 1)
//	{
//		ft_printf("%s %d %d\n", data.graph[i].name, data.graph[i].x, data.graph[i].y);
//		ft_printf("value %d  |  way %d \n", data.graph[i].value, data.graph[i].w);
//		n = 0;
//		while (n < data.graph[i].n_links)
//		{
//			if (data.graph[i].links[n]->w < LEMIN_MAX_WAYS && data.graph[i].links[n]->w > 0)
//			{
//				ft_printf("|%s ", data.graph[i].links[n]->name);
//				ft_printf("v(%d) ", data.graph[i].links[n]->value);
//				ft_printf("w(%d)| ", data.graph[i].links[n]->w);
//			}
//			++n;
//		}
//		ft_printf("\n\n");
//		++i;
//	}
//}

int main(int argc, char **argv)
{
	t_lemin_data	data;
	char			*input;

	(void)argv;
	(void)argc;
	if (!lemin_parse(&data, &input) || !lemin_find_way(&data))
	{
		//TODO free everything
		ft_printf("[greenUsage:~] ./lem-in\n[cyan%s", LEMIN_USAGE);
		return (0);
	}
//	ft_printf("%s", data.input);
	lemin_split_ants(&data);
	lemin_move_ants(&data);
	//TODO free everything
	return (1);
}
