/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:33:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 14:17:36 by dderevyn         ###   ########.fr       */
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
	unsigned int	i;

	input->buff = NULL;
	input->next = NULL;
	data->graph = NULL;
	data->n_rooms = 0;
	data->n_links = 0;
	data->n_ants = 0;
	i = 0;
	while (i < LEMIN_MAX_SOLUTIONS)
	{
		data->solutions[i].turns = 0;
		data->solutions[i].ways = NULL;
		data->solutions[i].n_ways = 0;
		data->solutions[i].ants = NULL;
		++i;
	}
}

int			main(int argc, char **argv)
{
	t_lemin_data	data;
	t_lemin_input	input;
	t_lemin_vis		vis;

	static_init(&data, &input);
	if (!lemin_parse(&data, &input) || !lemin_solution(&data))
	{
		ft_printf(LEMIN_USAGE, LEMIN_USAGE_MAP0);
		lemin_exit(&data, &input, &vis);
		return (0);
	}
	if (!lemin_vis_parse(&data, &vis, argc, argv))
	{
		lemin_exit(&data, &input, &vis);
		return (0);
	}
	if (vis.vis == 1)
		lemin_vis(&data, &vis);
	else
	{
		static_print_input(&input);
		lemin_move_ants(&data);
	}
	lemin_exit(&data, &input, &vis);
	return (1);
}
