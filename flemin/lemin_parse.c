/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:43 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/01 18:54:45 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_save_input(char **input, char **buff)
{
	ft_strninject(input, *buff, -1, -1);
	ft_strninject(input, "\n", -1, -1);
	ft_strdel(buff);
}

static void	static_init(t_lemin_parse *parse)
{
	parse->buff = NULL;
	parse->i = 0;
	parse->ants = 0;
	parse->start = 0;
	parse->end = 0;
	parse->start_next = 0;
	parse->end_next = 0;
	parse->rooms = 0;
	parse->valid_rooms = 0;
	parse->flag = 0;
}

static int	static_parse_hash2(t_lemin_data *data, t_lemin_parse *parse,
			char **buff)
{
	(void)data;
	(void)parse;
	if (ft_strncmp(*buff, LEMIN_CMND_END, -1))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_END0);
		ft_strdel(buff);
		return (0);
	}
	return (1);
}

static int	static_parse_hash(t_lemin_data *data, t_lemin_parse *parse,
			char **buff)
{
	if (!parse->start && !parse->end_next
	&& ft_strncmp(*buff, LEMIN_CMND_START, -1))
	{
		parse->start = 1;
		parse->start_next = 1;
		data->start = data->n_nodes;
		return (1);
	}
	if (!parse->end && !parse->start_next
	&& ft_strncmp(*buff, LEMIN_CMND_END, -1))
	{
		parse->end = 1;
		parse->end_next = 1;
		data->end = data->n_nodes;
		return (1);
	}
	if (ft_strncmp(*buff, LEMIN_CMND_START, -1))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_START0);
		ft_strdel(buff);
		return (0);
	}
	return (static_parse_hash2(data, parse, buff));
}

int			lemin_parse(t_lemin_data *data, char **input)
{
	t_lemin_parse	parse;

	static_init(&parse);
	while ((parse.flag || ft_gnl(0, &parse.buff) > 0) && parse.buff && parse.buff[0] != '*')//while (parse.flag || ft_gnl(0, &parse.buff) > 0)
	{
		if (parse.buff[0] != '#' && parse.ants && parse.valid_rooms
		&& !lemin_valid_link(data, &parse, &parse.buff, *input))
			return (0);
		else if (parse.buff[0] != '#' && parse.ants && !parse.valid_rooms
		&& !lemin_valid_room(data, &parse, &parse.buff))
			return (0);
		else if (parse.buff[0] != '#' && !parse.ants
		&& !lemin_parse_ants(data, &parse, &parse.buff, *input))
			return (0);
		else if (parse.buff[0] == '#'
		&& !static_parse_hash(data, &parse, &parse.buff))
			return (0);
		if (!parse.flag)
			static_save_input(input, &parse.buff);
	}
	ft_strdel(&parse.buff);
	if (!lemin_parse_links(data, &parse, *input))
		return (0);
	return (1);
}
