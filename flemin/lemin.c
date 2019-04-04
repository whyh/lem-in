/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:33:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/04 18:50:42 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_print_input(t_lemin_input *input)
{
	while (input && input->buff && input->buff[0])
	{
		ft_printf("%s\n", input->buff);
		input = input->next;
	}
}

static void	static_init(t_lemin_data *data, t_lemin_input *input)
{
	input->buff = NULL;
	input->next = NULL;
	data->graph = NULL;
	data->ways = NULL;
	data->ants = NULL;
	data->n_ways = 0;
	data->n_nodes = 0;
	data->n_links = 0;
	data->n_ants = 0;
}

static void	static_free_2(t_lemin_data *data, t_lemin_input *input)
{
	t_lemin_input	*prev;

	if (input->buff)
		ft_strdel(&input->buff);
	if (input->next)
	{
		input = input->next;
		while (input)
		{
			if (input->buff)
				ft_strdel(&input->buff);
			prev = input;
			input = input->next;
			ft_memdel((void**)(&prev));
		}
	}
	if (data->ants)
		ft_memdel((void**)(&data->ants));
}

static void	static_free(t_lemin_data *data, t_lemin_input *input)
{
	unsigned int	i;

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
	if (data->ways)
	{
		i = 0;
		while (i++ < data->n_ways)
			ft_memdel((void **)(&data->ways[i - 1].path));
		ft_memdel((void **)(&data->ways));
	}
	static_free_2(data, input);
}

int			main(int argc, char **argv)
{
	t_lemin_data	data;
	t_lemin_input	input;
	t_lemin_vis		vis;

	if (!lemin_vis_parse(argc, argv, &vis))
		return (0);
	static_init(&data, &input);
	if (!lemin_parse(&data, &input) || !lemin_find_way(&data))
	{
		static_free(&data, &input);
		ft_printf(LEMIN_USAGE, LEMIN_USAGE_MAP0);
		return (0);
	}
	lemin_split_ants(&data);
	if (vis.vis == LEMIN_INPROGRESS)
		lemin_vis(&data, &vis);
	else
	{
		static_print_input(&input);
		lemin_move_ants(&data);
	}
	static_free(&data, &input);
	return (1);
}
