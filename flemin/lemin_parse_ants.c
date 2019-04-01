/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_parse_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 19:10:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/01 19:53:23 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid(t_lemin_parse *parse, const char *buff)
{
	unsigned int	tmp_i;

	tmp_i = 0;
	if (parse->start_next)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_START1);
		return (0);
	}
	if (parse->end_next)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_END1);
		return (0);
	}
	if (ft_strin(SIGNS, buff[tmp_i]))
		++tmp_i;
	while (ft_strin(DEC, buff[tmp_i]))
		++tmp_i;
	if (!buff[0] || buff[tmp_i] != '\0')
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ANT0);
		return (0);
	}
	parse->i += tmp_i + 1;
	return (1);
}

int			lemin_parse_ants(t_lemin_data *data, t_lemin_parse *parse,
			char **buff, char *input)
{
	long long	n_ants;

	while (input && input[parse->i] == '#')
		parse->i += ft_strchr_i(&(input[parse->i]), '\n') + 1;
	if (!static_valid(parse, *buff))
	{
		ft_strdel(buff);
		return (0);
	}
	n_ants = ft_atoibase(DEC, *buff);
	if (n_ants < LEMIN_MIN_ANTS || n_ants > LEMIN_MAX_ANTS)
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_ANT1);
		ft_strdel(buff);
		return (0);
	}
	data->n_ants = (UI)n_ants;
	parse->ants = 1;
	return (1);
}
