/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_valid_room.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:38:12 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 17:10:11 by dderevyn         ###   ########.fr       */
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
			const char *buff)
{
	if (buff[0] <= 32 || buff[0] >= 127 || buff[0] == 'L')
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM0);
		return (0);
	}
	if (!static_valid(buff))
	{
		if (!ft_strin(buff, '-') || ft_strin(buff, ' '))
		{
			ft_printf(LEMIN_ERR, LEMIN_ERR_ROOM1);
			return (0);
		}
		parse->rooms = LEMIN_INPROGRESS;
	}
	else
	{
		if (parse->start == LEMIN_INPROGRESS)
			parse->start = LEMIN_DONE;
		else if (parse->end == LEMIN_INPROGRESS)
			parse->end = LEMIN_DONE;
		data->n_rooms++;
	}
	return (1);
}
