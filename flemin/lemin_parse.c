/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:43 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/03 19:00:32 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_parse_hash(t_lemin_data *data, t_lemin_parse *parse,
			const char *buff)
{
	if (ft_strncmp(buff, LEMIN_CMND_START, -1))
	{
		data->start = data->n_nodes;
		if (parse->start != LEMIN_NDONE)
			ft_printf(LEMIN_ERR, LEMIN_ERR_START3);
		else if ((parse->start = LEMIN_INPROGRESS)
		&& parse->end == LEMIN_INPROGRESS)
			ft_printf(LEMIN_ERR, LEMIN_ERR_START0);
		else
			return (1);
		return (0);
	}
	if (ft_strncmp(buff, LEMIN_CMND_END, -1))
	{
		data->end = data->n_nodes;
		if (parse->end != LEMIN_NDONE)
			ft_printf(LEMIN_ERR, LEMIN_ERR_END3);
		else if ((parse->end = LEMIN_INPROGRESS)
		&& parse->start == LEMIN_INPROGRESS)
			ft_printf(LEMIN_ERR, LEMIN_ERR_END0);
		else
			return (1);
		return (0);
	}
	return (1);
}

static int	static_loop(t_lemin_data *data, t_lemin_input *input,
			t_lemin_parse *parse)
{
	if (input->buff[0] == '#')
	{
		if (parse->ants == LEMIN_NDONE)
			parse->line++;
		if (!static_parse_hash(data, parse, input->buff))
			return (0);
	}
	else if (parse->ants == LEMIN_NDONE)
	{
		if (!lemin_parse_ants(data, parse, input->buff))
			return (0);
	}
	else if (parse->rooms == LEMIN_NDONE)
	{
		if (!lemin_valid_room(data, parse, input->buff))
			return (0);
	}
	else if (parse->rooms == LEMIN_DONE)
	{
		if (!lemin_valid_link(data, input->buff))
			return (0);
	}
	return (1);
}

static void	static_init(t_lemin_parse *parse, t_lemin_input *input)
{
	parse->input = input;
	parse->line = 0;
	parse->ants = 0;
	parse->start = 0;
	parse->end = 0;
	parse->rooms = 0;
}

int			lemin_parse(t_lemin_data *data, t_lemin_input *input)
{
	t_lemin_parse	parse;

	static_init(&parse, input);
	while (ft_gnl(0, &input->buff) > 0
	&& input->buff && input->buff[0] != '*')//TODO rm
	{
		if (!static_loop(data, input, &parse))
			return (0);
		if (parse.rooms == LEMIN_INPROGRESS)
		{
			if (!lemin_parse_rooms(data, &parse, parse.input)
			|| !static_loop(data, input, &parse))
				return (0);
		}
		input->next = ft_memalloc(sizeof(t_lemin_input));
		input = input->next;
		input->buff = NULL;
		input->next = NULL;
	}
	if (!lemin_parse_links(data, &parse, parse.input))
		return (0);
	return (1);
}
