/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:10:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/03 17:39:18 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid(const char *buff)
{
	unsigned int	i;

	i = 0;
	if (ft_strin(SIGNS, buff[i]))
		++i;
	while (ft_strin(DEC, buff[i]))
		++i;
	if (!buff[0] || buff[i])
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ANT0);
		return (0);
	}
	return (1);
}

int			lemin_parse_ants(t_lemin_data *data, t_lemin_parse *parse,
			const char *buff)
{
	long long	n_ants;

	if (parse->start != LEMIN_NDONE)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_START1);
		return (0);
	}
	if (parse->end != LEMIN_NDONE)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_END1);
		return (0);
	}
	if (!static_valid(buff))
		return (0);
	n_ants = ft_atoibase(DEC, buff);
	if (n_ants < LEMIN_MIN_ANTS || n_ants > LEMIN_MAX_ANTS)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ANT1);
		return (0);
	}
	data->n_ants = (UI)n_ants;
	parse->ants = LEMIN_DONE;
	parse->line++;
	return (1);
}
