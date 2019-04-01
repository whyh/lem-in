/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:53:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/01 17:22:18 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			static_valid(t_lemin_data *data, int room0, int room1)
{
	unsigned int i;

	if (ft_strncmp(data->graph[room0].name, data->graph[room1].name, -1))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_LINK2);
		return (0);
	}
	i = 0;
	while (data->graph[room0].links && data->graph[room0].links[i])
	{
		if (data->graph[room0].links[i]->name == data->graph[room1].name)
		{
			ft_printf(LEMIN_ERR, LEMIN_ERR_LINK3);
			return (0);
		}
		++i;
	}
	return (1);
}

static unsigned int	static_get_room(t_lemin_data data, t_lemin_parse *parse,
					char *input, unsigned int part)
{
	unsigned int	tmp_i;
	char			*link;
	unsigned int	room;

	if (part == 0)
		tmp_i = (UI)ft_strchr_i(&(input[parse->i]), '-');
	else if (part == 1)
		tmp_i = (UI)ft_strchr_i(&(input[parse->i]), '\n');
	else
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_STD);
		return (0);
	}
	link = ft_strndup(&(input[parse->i]), tmp_i);
	parse->i += tmp_i + 1;
	room = (UI)lemin_find_node(data, link, 0);
	ft_strdel(&link);
	return (room);
}

static void			static_store(t_lemin_data *data, unsigned int room,
					unsigned int link_room)
{
	unsigned int	i;
	t_lemin_node	*node;

	node = &(data->graph[room]);
	if (!node->links)
	{
		node->links = ft_memalloc(sizeof(t_lemin_node*) * (node->n_links + 1));
		node->links[node->n_links] = NULL;
	}
	i = 0;
	while (node->links[i] != NULL)
		++i;
	node->links[i] = &(data->graph[link_room]);
}

int					lemin_parse_links(t_lemin_data *data, t_lemin_parse *parse,
					char *input)
{
	unsigned int	link;
	unsigned int	room0;
	unsigned int	room1;

	link = 0;
	while (link < data->n_links)
	{
		while (input[parse->i] == '#')
			parse->i += ft_strchr_i(&(input[parse->i]), '\n') + 1;
		room0 = static_get_room(*data, parse, input, 0);
		room1 = static_get_room(*data, parse, input, 1);
		if (!static_valid(data, room0, room1))
			return (0);
		static_store(data, room0, room1);
		static_store(data, room1, room0);
		++link;
	}
	return (1);
}
