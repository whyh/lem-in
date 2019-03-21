/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:23:39 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 19:51:24 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int lemin_find_node(t_lemin_data *data, const char *name, unsigned int start)
{
	unsigned int	i;

	i = start;
	while (i < data->n_nodes && !ft_strncmp(data->graph[i].name, name, -1))
		++i;
	if (!ft_strncmp(data->graph[i].name, name, -1))
		return (-1);
	return (i);
}
