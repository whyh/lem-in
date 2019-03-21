/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 20:09:43 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/21 15:13:30 by dderevyn         ###   ########.fr       */
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
	while (data->n_nodes > 0)
	{
		if (data->graph[data->n_nodes].name)
			ft_strdel(&(data->graph[data->n_nodes].name));
		if (data->graph[data->n_nodes].links)
			ft_memdel((void**)(data->graph[data->n_nodes].links));
		data->n_nodes--;
	}
	if (data->graph)
		ft_memdel((void**)(data->graph));
	return (1);
}

static void	static_init(t_lemin_data *data)
{
	data->i = 0;
	data->n_nodes = 0;
	data->n_links = 0;
	data->start = LEMIN_UNSPEC;
	data->end = LEMIN_UNSPEC;
	data->graph = NULL;
}

static void	static_error(t_lemin_data *data)
{
	if (data->start == LEMIN_BEING_SPEC || data->start == LEMIN_UNSPEC)
		ft_printf("[redError: missing start of the farm\n");
	else if (data->end == LEMIN_BEING_SPEC || data->end == LEMIN_UNSPEC)
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
	if (!lemin_parse_rooms(data) && static_dell(data))
		return (0);
	if (ret == 0 || data->start == LEMIN_UNSPEC || data->end == LEMIN_UNSPEC
	|| data->start == LEMIN_BEING_SPEC || data->end == LEMIN_BEING_SPEC
	|| data->start == data->end)
	{
		if (ret != 0)
			static_error(data);
		ft_strdel(&buff);
		return (0);
	}
	while (buff || (ft_gnl(0, &buff) > 0 && buff && buff[0] != '*'))//while (buff || (ft_gnl(0, &buff) > 0)
	{
		if (!lemin_valid_links(data, buff) && static_dell(data))
			return(0);
		lemin_parse_compose(data, &buff);
	}
	if (!lemin_parse_links(data) && static_dell(data))
		return (0);
	return (1);
}
