/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_rooms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:52:24 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 21:42:56 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_prop(t_lemin_data *data, int room)
{
	int	tmp_room;

	if (data->graph[room].x < 0 || data->graph[room].x > LEMIN_MAX_COORDS
	|| data->graph[room].y < 0 || data->graph[room].y > LEMIN_MAX_COORDS)
	{
		ft_printf("[redErorr: at least one coordinate isn't in the range ");
		ft_printf("%d - %d\n", LEMIN_MIN_COORDS, LEMIN_MAX_COORDS);
		return (0);
	}
	tmp_room = 0;
	while (tmp_room < room)
	{
		if (ft_strncmp(data->graph[tmp_room].name, data->graph[room].name, -1)
		|| (data->graph[tmp_room].x == data->graph[room].x
		&& data->graph[tmp_room].y == data->graph[room].y))
		{
			ft_printf("[redErorr: %s",
			"at least one parameter in the room specification is duplicated\n");
			return (0);
		}
		++tmp_room;
	}
	return (1);
}

static void	static_get_coord(t_lemin_data *data, char coord, int room)
{
	if (coord == 'x')
		data->graph[room].x = (int)ft_atoibase(DEC, &(data->input[data->i]));
	else
		data->graph[room].y = (int)ft_atoibase(DEC, &(data->input[data->i]));
	if (data->input[data->i] == '+')
		data->i++;
	while (ft_strin(DEC, data->input[data->i]))
		data->i++;
	data->i++;
}

int			lemin_parse_rooms(t_lemin_data *data)
{
	int	room;
	int	tmp_i;

	data->graph = ft_memalloc(sizeof(t_lemin_data) * (data->node + 1));
	room = 0;
	while (room <= data->node)
	{
		while (data->input[data->i] == '#')
			lemin_parse_skip_comment(data);
		tmp_i = (int)ft_strchr_i(&(data->input[data->i]), ' ');
		data->graph[room].name = ft_strndup(&(data->input[data->i]), tmp_i);
		data->graph[room].value = -1;
		data->i += tmp_i + 1;
		static_get_coord(data, 'x', room);
		static_get_coord(data, 'y', room);
		if (!static_valid_prop(data, room))
			return (0);
		++room;
	}
	return (1);
}

static int	static_valid(t_lemin_data *data, char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != ' ')
		++i;
	if (buff[i] != ' ')
		return (0);
	++i;
	if (buff[i] == '+' || buff[i] == '-')
		++i;
	while (ft_strin(DEC, buff[i]))
		++i;
	if (buff[i] != ' ')
		return (0);
	++i;
	if (buff[i] == '+' || buff[i] == '-')
		++i;
	while (ft_strin(DEC, buff[i]))
		++i;
	if (buff[i])
		return (0);
	data->node++;
	if (data->start == -2)
		data->start = data->node;
	if (data->end == -2)
		data->end = data->node;
	return (1);
}

int			lemin_valid_rooms(t_lemin_data *data, char *buff)
{
	if ((buff[0] <= 32 || buff[0] >= 127 || buff[0] == 'L')
	&& ft_printf("[redError: invalid symbol in the room specification\n"))
		return (0);
	if (ft_strncmp(buff, "##start", -1))
	{
		if (data->start == -1)
			data->start = -2;
		else
		{
			ft_printf("[redError: farm start specified more than once\n");
			return (0);
		}
	}
	else if (ft_strncmp(buff, "##end", -1))
	{
		if (data->end == -1)
			data->end = -2;
		else
		{
			ft_printf("[redError: farm end specified more than once\n");
			return (0);
		}
	}
	else if (buff[0] != '#' && !static_valid(data, buff))
	{
		if (!ft_strin(buff, '-') || ft_strin(buff, ' '))
		{
			ft_printf("[redError: invalid room specification\n");
			return (0);
		}
		return (-1);
	}
	return (1);
}
