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

static void	static_init(t_lemin_data *data, char **input)
{
	*input = NULL;
	data->graph = NULL;
	data->ways = NULL;
	data->ants = NULL;
	data->n_ways = 0;
	data->n_nodes = 0;
	data->n_links = 0;
	data->n_ants = 0;
}

static void	static_free_2(t_lemin_data *data)
{
	unsigned int	i;

	if (data->ways)
	{
		i = 0;
		while (i < data->n_ways)
		{
			ft_memdel((void**)(&data->ways[i].path));
			++i;
		}
		ft_memdel((void**)(&data->ways));
	}
}

static void	static_free(t_lemin_data *data, char **input)
{
	unsigned int	i;

	if (input && *input)
		ft_strdel(input);
	if (data->graph)
	{
		i = 0;
		while (i < data->n_nodes && data->graph[i].name)
		{
			if (data->graph[i].name)
				ft_strdel(&(data->graph[i].name));
			if (data->graph[i].links)
				ft_memdel((void**)(&data->graph[i].links));
			++i;
		}
		ft_memdel((void**)(&data->graph));
	}
	if (data->ants)
		ft_memdel((void**)(&data->ants));
	static_free_2(data);
}

int main(int argc, char **argv)
{
	t_lemin_data	data;
	char			*input;

	(void)argv;
	(void)argc;
	static_init(&data, &input);
	if (!lemin_parse(&data, &input) || !lemin_find_way(&data))
	{
		static_free(&data, &input);
		ft_printf(LEMIN_USAGE, LEMIN_USAGE_MAP0);
		return (0);
	}
//	ft_printf("%s", input);
	lemin_split_ants(&data);
	lemin_move_ants(&data);
	static_free(&data, &input);
	return (1);
}
