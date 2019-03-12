/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:10:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 21:12:21 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid(t_lemin_data *data, char **buff)
{
	while (ft_gnl(0, buff) > 0 && (*buff)[0] == '#')
	{
		if (ft_strncmp(*buff, "##start", -1) || ft_strncmp(*buff, "##end", -1))
		{
			if (ft_strncmp(*buff, "##start", -1))
				ft_printf(
				"[redError: \"start\" command before the ant specification\n");
			else
				ft_printf(
				"[redError: \"end\" command before the ant specification\n");
			ft_strdel(buff);
			return (0);
		}
		data->i += ft_strlen(*buff) + 1;
		lemin_parse_compose(data, buff);
	}
	data->ants = ft_atoibase(DEC, buff[0]);
	if (data->ants <= 0)
	{
		ft_strdel(buff);
		ft_printf("[redError: invalid number of ants\n");
		return (0);
	}
	return (1);
}

int			lemin_parse_ants(t_lemin_data *data, char *buff)
{
	int	tmp_i;

	if (!static_valid(data, &buff))
		return (0);
	if (data->ants > LEMIN_MAX_ANTS && ft_printf(
	"[redError: max supported number of ants is %d\n", LEMIN_MAX_ANTS))
	{
		ft_strdel(&buff);
		return (0);
	}
	tmp_i = 0;
	if (buff[tmp_i] == '+')
		tmp_i++;
	while (ft_strin(DEC, buff[tmp_i]))
		tmp_i++;
	if (buff[tmp_i] != '\0'
	&& ft_printf("[redError: invalid symbol in the first line\n"))
	{
		ft_strdel(&buff);
		return (0);
	}
	data->i += tmp_i + 1;
	lemin_parse_compose(data, &buff);
	return (1);
}
