/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:23:39 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 17:10:11 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int	lemin_find_node(t_lemin_data data, const char *name, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (i < data.n_rooms)
	{
		if (ft_strncmp(data.graph[i].name, name, -1))
			return (i);
		++i;
	}
	return (-1);
}
