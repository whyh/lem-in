/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 21:33:51 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/13 15:13:48 by dderevyn         ###   ########.fr       */
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

static void	static_init(t_lemin_data *data, t_lemin_input *input,
			t_lemin_vis *vis)
{
	vis->vis = 0;
	input->buff = NULL;
	input->next = NULL;
	data->graph = NULL;
	data->ways = NULL;
	data->ants = NULL;
	data->n_rooms = 0;
	data->n_links = 0;
	data->n_ants = 0;
}

int			main(int argc, char **argv)
{
	t_lemin_data	data;
	t_lemin_input	input;
	t_lemin_vis		vis;

	static_init(&data, &input, &vis);
	if (!lemin_parse(&data, &input) || !lemin_find_way(&data))
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
