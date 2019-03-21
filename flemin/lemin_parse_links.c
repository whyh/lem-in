/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:53:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/14 17:51:05 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_name(t_lemin_data *data, char *room)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_nodes && !ft_strncmp(data->graph[i].name, room, -1))
		++i;
	if (!ft_strncmp(data->graph[i].name, room, -1))
	{
		ft_printf("[redError: link leads to non existing room\n");
		return (0);
	}
	return (1);
}

static int static_valid(t_lemin_data *data, int room0, int room1)
{
	unsigned int i;

	if (!static_valid_name(data, data->graph[room0].name)
	|| !static_valid_name(data, data->graph[room1].name))
		return (0);
	if (ft_strncmp(data->graph[room0].name, data->graph[room1].name, -1))
	{
		ft_printf("[redError: room is linked do itself\n");
		return (0);
	}
	i = 0;
	while (data->graph[room0].links && data->graph[room0].links[i])
	{
		if (data->graph[room0].links[i]->name == data->graph[room1].name)
		{
			ft_printf("[redError: duplicate of link\n");
			return (0);
		}
		++i;
	}
	return (1);
}

int			lemin_parse_links(t_lemin_data *data)
{
	unsigned int		i;
	unsigned int 	room0;
	unsigned int 	room1;
	char	*link0;
	char	*link1;
	unsigned int		tmp_i;
	unsigned int 	n;

	i = 0;
	while (i < data->n_links)
	{
		while (data->input[data->i] == '#')
			lemin_parse_skip_comment(data);
		tmp_i = (int)ft_strchr_i(&(data->input[data->i]), '-');
		link0 = ft_strndup(&(data->input[data->i]), tmp_i);
		data->i += tmp_i + 1;
		tmp_i = (int)ft_strchr_i(&(data->input[data->i]), '\n');
		link1 = ft_strndup(&(data->input[data->i]), tmp_i);
		data->i += tmp_i + 1;
		room0 = (UI)lemin_find_node(data, link0, 0);
		room1 = (UI)lemin_find_node(data, link1, 0);
		ft_strdel(&link0);
		ft_strdel(&link1);
		if (!static_valid(data, room0, room1))
			return (0);
		n = 0;
		if (!data->graph[room0].links)
		{
			data->graph[room0].links = ft_memalloc(
			sizeof(t_lemin_node*) * (data->graph[room0].n_links + 1));
			data->graph[room0].links[data->graph[room0].n_links] = NULL;
		}
		while (data->graph[room0].links[n] != NULL)
			++n;
		data->graph[room0].links[n] = &(data->graph[room1]);
		n = 0;
		if (!data->graph[room1].links)
		{
			data->graph[room1].links = ft_memalloc(
					sizeof(t_lemin_node*) * (data->graph[room1].n_links + 1));
			data->graph[room1].links[data->graph[room1].n_links] = NULL;
		}
		while (data->graph[room1].links[n] != NULL)
			++n;
		data->graph[room1].links[n] = &(data->graph[room0]);
		++i;
	}
	return (1);
}

int			lemin_valid_links(t_lemin_data *data, char *buff)
{
	int 	i;
	int 	room0;
	int 	room1;
	char	*link0;
	char	*link1;

	if ((buff[0] <= 32 || buff[0] >= 127 || buff[0] == 'L' || buff[0] == '-')
	&& ft_printf("[redError: invalid symbol in the link specification\n"))
		return (0);
	if (ft_strncmp(buff, "##start", -1)
	&& ft_printf("[redError: \"start\" command in the link specification\n"))
		return (0);
	if (ft_strncmp(buff, "##end", -1)
	&& ft_printf("[redError: \"end\" command in the link specification\n"))
		return (0);
	if (buff[0] != '#')
	{
		i = 0;
		while (buff[i] && buff[i] != '-')
			++i;
		link0 = ft_strndup(buff, i);
		if ((!buff[i] || !buff[i + 1])
		&& ft_printf("[redError: invalid link specification\n"))
			return (0);
		link1 = ft_strndup(&(buff[i + 1]), -1);
		if ((room0 = lemin_find_node(data, link0, 0)) == -1
		|| (room1 = lemin_find_node(data, link1, 0)) == -1)
			return (0);
		ft_strdel(&link0);
		ft_strdel(&link1);
		data->graph[room0].n_links++;
		data->graph[room1].n_links++;
		data->n_links++;
	}
	return (1);
}
