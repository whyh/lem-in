/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_links.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:53:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 22:23:20 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_name(t_lemin_data *data, char *room)
{
	int	i;

	i = 0;
	while (i < data->node && !ft_strncmp(data->graph[i].name, room, -1))
		++i;
	if (!ft_strncmp(data->graph[i].name, room, -1))
	{
		ft_printf("[redError: link leads to non existing room\n");
		return (0);
	}
	return (1);
}

static int static_valid(t_lemin_data *data, int link)
{
	int	i;

	if (!static_valid_name(data, data->link0[link])
	|| !static_valid_name(data, data->link1[link])
	|| ft_strncmp(data->link0[link], data->link1[link], -1))
	{
		if (ft_strncmp(data->link0[link], data->link1[link], -1))
			ft_printf("[redError: room is linked do itself\n");
		return (0);
	}
	i = 0;
	while (i < link)
	{
		if ((ft_strncmp(data->link0[i], data->link0[link], -1)
		&& ft_strncmp(data->link1[i], data->link1[link], -1))
		|| (ft_strncmp(data->link1[i], data->link0[link], -1)
		&& ft_strncmp(data->link0[i], data->link1[link], -1)))
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
	int	link;
	int	tmp_i;

	data->link0 = ft_memalloc(sizeof(t_lemin_data*) * (data->link + 1));
	data->link1 = ft_memalloc(sizeof(t_lemin_data*) * (data->link + 1));
	link = 0;
	while (link <= data->link)
	{
		while (data->input[data->i] == '#')
			lemin_parse_skip_comment(data);
		tmp_i = (int)ft_strchr_i(&(data->input[data->i]), '-');
		data->link0[link] = ft_strndup(&(data->input[data->i]), tmp_i);
		data->i += tmp_i + 1;
		tmp_i = (int)ft_strchr_i(&(data->input[data->i]), '\n');
		data->link1[link] = ft_strndup(&(data->input[data->i]), tmp_i);
		data->i += tmp_i + 1;
		if (!static_valid(data, link))
			return (0);
		++link;
	}
	return (1);
}

int			lemin_valid_links(t_lemin_data *data, char *buff)
{
	int i;

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
		if ((!buff[i] || !buff[i + 1])
		&& ft_printf("[redError: invalid link specification\n"))
			return (0);
		data->link++;
	}
	return (1);
}
