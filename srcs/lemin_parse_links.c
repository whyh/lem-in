/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:53:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 17:10:11 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			static_store(t_lemin_data *data, unsigned int room,
					unsigned int link_room)
{
	unsigned int	i;
	t_lemin_room	*node;

	node = &(data->graph[room]);
	if (!node->links)
	{
		node->links = ft_memalloc(sizeof(t_lemin_room*) * (node->n_links + 1));
		i = 0;
		while (i <= node->n_links)
		{
			node->links[i] = NULL;
			++i;
		}
	}
	i = 0;
	while (node->links[i] != NULL)
		++i;
	node->links[i] = &(data->graph[link_room]);
}

static int			static_valid(t_lemin_data *data, unsigned int room0,
					unsigned int room1)
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
			data->graph[room0].n_links--;
			return (1);
		}
		++i;
	}
	static_store(data, room0, room1);
	static_store(data, room1, room0);
	return (1);
}

static unsigned int	static_get_room(t_lemin_data data, char *input,
					unsigned int *i)
{
	unsigned int	tmp_i;
	unsigned int	room;
	char			*link;

	if (*i == 0)
		tmp_i = (UI)ft_strchr_i(&(input[*i]), '-');
	else
		tmp_i = (UI)ft_strchr_i(&(input[*i]), '\n');
	link = ft_strndup(&(input[*i]), tmp_i);
	*i += tmp_i + 1;
	room = (UI)lemin_find_node(data, link, 0);
	ft_strdel(&link);
	return (room);
}

int					lemin_parse_links(t_lemin_data *data, t_lemin_parse *parse,
					t_lemin_input *input)
{
	unsigned int	room0;
	unsigned int	room1;
	unsigned int	link;
	unsigned int	i;

	i = 0;
	while (i++ < parse->line)
		input = input->next;
	link = 0;
	while (link++ < data->n_links)
	{
		while (input->buff[0] == '#')
		{
			input = input->next;
			parse->line++;
		}
		i = 0;
		room0 = static_get_room(*data, input->buff, &i);
		room1 = static_get_room(*data, input->buff, &i);
		if (!static_valid(data, room0, room1))
			return (0);
		input = input->next;
		parse->line++;
	}
	return (1);
}
