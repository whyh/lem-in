/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_valid_link.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 20:32:02 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 17:10:11 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_names(t_lemin_data *data, const char *buff, int i)
{
	char	*link0;
	char	*link1;
	int		room0;
	int		room1;

	link0 = ft_strndup(buff, i);
	if (!buff[i] || !buff[i + 1])
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_LINK0);
		return (0);
	}
	link1 = ft_strndup(&(buff[i + 1]), -1);
	if (((room0 = lemin_find_node(*data, link0, 0)) == -1)
	|| ((room1 = lemin_find_node(*data, link1, 0)) == -1))
	{
		ft_strdel(&link0);
		ft_strdel(&link1);
		ft_printf(LEMIN_ERR, LEMIN_ERR_LINK1);
		return (0);
	}
	ft_strdel(&link0);
	ft_strdel(&link1);
	data->graph[room0].n_links++;
	data->graph[room1].n_links++;
	return (1);
}

int			lemin_valid_link(t_lemin_data *data, char *buff)
{
	unsigned int	i;

	if (buff[0] <= 32 || buff[0] >= 127 || buff[0] == 'L' || buff[0] == '-')
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_LINK0);
		return (0);
	}
	i = 0;
	while (buff[i] && buff[i] != '-')
		++i;
	if (!static_valid_names(data, buff, i))
		return (0);
	data->n_links++;
	return (1);
}
