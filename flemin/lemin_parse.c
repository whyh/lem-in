/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:43 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 21:47:35 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_parse_compose(t_lemin_data *data, char **buff)
{
	ft_strninject(&(data->input), *buff, -1, -1);
	ft_strninject(&(data->input), "\n", -1, -1);
	ft_strdel(buff);
}

void	lemin_parse_skip_comment(t_lemin_data *data)
{
	while (data->input[data->i] && data->input[data->i] != '\n')
		data->i++;
	if (data->input[data->i] == '\n')
		data->i++;
}

static int	static_dell(t_lemin_data *data)
{
	int	i;

	i = 0;
	while (data->link0 && i < data->link && data->link0[i])
	{
		ft_strdel(&(data->link1[i]));
		ft_strdel(&(data->link0[i]));
		++i;
	}
	if (data->link0)
		ft_memdel((void**)data->link0);
	if (data->link1)
		ft_memdel((void**)data->link1);
	i = 0;
	while (data->graph && i < data->node)
	{
		if (data->graph[i].name)
			ft_strdel(&(data->graph[i].name));
		++i;
	}
	if (data->graph)
		ft_memdel((void**)(data->graph));
	return (1);
}

static void	static_init(t_lemin_data *data)
{
	data->i = 0;
	data->node = -1;
	data->start = -1;
	data->end = -1;
	data->link = -1;
	data->link0 = NULL;
	data->link1 = NULL;
	data->graph = NULL;
}

static void	static_error(t_lemin_data *data)
{
	if (data->start < 0)
		ft_printf("[redError: missing start of the farm\n");
	else if (data->end < 0)
		ft_printf("[redError: missing end of the farm\n");
	else if (data->start == data->end)
		ft_printf(
		"[redError: start and end of the farm are in the same point\n");
}

int			lemin_parse(t_lemin_data *data)
{
	char	*buff;
	int		ret;

	static_init(data);
	if (!lemin_parse_ants(data, NULL) && static_dell(data))
		return (0);
	while (ft_gnl(0, &buff) > 0 && (ret = lemin_valid_rooms(data, buff)) > 0)
		lemin_parse_compose(data, &buff);
	if (ret == 0 || data->start < 0 || data->end < 0
	|| data->start == data->end)
	{
		if (ret != 0)
			static_error(data);
		ft_strdel(&buff);
		return (0);
	}
	while (buff || (ft_gnl(0, &buff) > 0 && buff[0] != '*'))//while (buff || (ft_gnl(0, &buff) > 0)
	{
		if (!lemin_valid_links(data, buff) && static_dell(data))
			return(0);
		lemin_parse_compose(data, &buff);
	}
	if ((!lemin_parse_rooms(data) || !lemin_parse_links(data))
	&& static_dell(data))
		return (0);
	return (1);
}
