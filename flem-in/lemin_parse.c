/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:43 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/06 21:58:34 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

static int	static_parse_ants(t_lemin_data *data)
{
	int	i;

	ft_gnl(1, &(data->input));
	if ((data->ants = (int)ft_atoibase(DEC, &(data->input[i]))) <= 0)
	{
		ft_printf("[redError: invalid number of ants");
		ft_strdel(&(data->input));
		return (0);
	}
	i = 0;
	if (data->input[i] == '+')
		++i;
	while (ft_strin(DEC, data->input[i]))
		++i;
	if (data->input[i] != '\0')
	{
		ft_printf("[redError: invalid symbol in the first line");
		ft_strdel(&(data->input));
		return (0);
	}
	return (1);
}

static int	static_parse_hash(t_lemin_parse *parse_data)
{
	if (parse_data->buff[1] != '#')
		return (1);
	if (parse_data->start == 0 && ft_strncmp(parse_data->buff, "##start", -1))
	{
		parse_data->start_next = 1;
		return (1);
	}
	if (parse_data->start == 1 && parse_data->end == 0
	&& ft_strncmp(parse_data->buff, "##end", -1))
	{
		parse_data->end_next = 1;
		return (1);
	}
	ft_printf("[redError: invalid farm specification");
	ft_strdel(&(parse_data->buff));
	return (0);
}

static int	static_parse_rooms(t_lemin_data *data, t_lemin_parse *parse_data)
{
	int	i;

	if (parse_data->buff[0] == 'L' || parse_data->buff[0] == ' ')
	{
		ft_printf("[redError: invalid room specification");
		ft_strdel(&(parse_data->buff));
		return (0);
	}
	i = 0;
	while (parse_data->buff[i] > 32 && parse_data->buff[i] < 127
	&& parse_data->buff[i] != 'L' && i <= 1000)
		++i;
	if (parse_data->buff[i] != ' ')
	{
		ft_printf("[redError: invalid room specification");
		ft_strdel(&(parse_data->buff));
		return (0);
	}
	parse_data->node = ft_memalloc(sizeof(t_lemin_node));
	if (parse_data->start_next)
	{
		parse_data->start_next = 0;
		parse_data->start = 1;
		data->start_node = parse_data->node;
	}
	else if (parse_data->end_next)
	{
		parse_data->end_next = 0;
		parse_data->end = 1;
		data->end_node = parse_data->node;
	}
	parse_data->node->name = ft_strndup(parse_data->buff, i);
	if (parse_data->buff[i])
		++i;
	parse_data->node->x = (int)ft_atoibase(DEC, &(parse_data->buff[i]));
	if (parse_data->node->x < 0 || parse_data->node->y < 0)
	{
		return (0);
	}
	if (parse_data->buff[i])
	return (1);
}

static int	static_parse_links(t_lemin_data *data, t_lemin_parse *parse_data)
{
	ft_printf("[redError: invalid link specification");
	ft_strdel(&(parse_data.buff));

	return (1);
}

int			lemin_parse(t_lemin_data *data)
{
	t_lemin_parse	parse_data;

	parse_data.start = 0;
	parse_data.end = 0;
	parse_data.start_next = 0;
	parse_data.end_next = 0;
	if (!static_parse_ants(data))
		return (0);
	while (ft_gnl(1, &(parse_data.buff)))
	{
		if (!parse_data.buff || !parse_data.buff[0] ||
		parse_data.buff[0] == '#')
		{
			if (!parse_data.buff || !parse_data.buff[0] ||
			!static_parse_hash(&parse_data))
				return (0);
		}
		else if (parse_data.end)
		{
			if (!static_parse_links(data, &parse_data))
				return (0);
		}
		else if (!static_parse_rooms(data, &parse_data))
			return (0);
		ft_strdel(&(parse_data.buff));
	}
	return (1);
}
