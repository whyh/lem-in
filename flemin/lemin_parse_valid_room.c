/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_valid_room.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:38:12 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/28 20:01:21 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid(const char *buff)
{
	int	i;

	i = 0;
	while (buff[i] && buff[i] != ' ')
		++i;
	if (buff[i] != ' ')
		return (0);
	++i;
	if (ft_strin(SIGNS, buff[i]))
		++i;
	while (ft_strin(DEC, buff[i]))
		++i;
	if (buff[i] != ' ')
		return (0);
	++i;
	if (ft_strin(SIGNS, buff[i]))
		++i;
	while (ft_strin(DEC, buff[i]))
		++i;
	if (buff[i])
		return (0);
	return (1);
}

int			lemin_valid_room(t_lemin_data *data, t_lemin_parse *parse,
			char **buff)
{
	if ((*buff)[0] <= 32 || (*buff)[0] >= 127 || (*buff)[0] == 'L')
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM0);
		ft_strdel(buff);
		return (0);
	}
	if (!static_valid(*buff))
	{
		if (!ft_strin(*buff, '-') || ft_strin(*buff, ' '))
		{
			ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM1);
			ft_strdel(buff);
			return (0);
		}
		parse->valid_rooms = 1;
	}
	else
	{
		if (parse->start_next)
			parse->start_next = 0;
		else if (parse->end_next)
			parse->end_next = 0;
		data->n_nodes++;
	}
	return (1);
}
