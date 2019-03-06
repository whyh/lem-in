/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:13:38 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/06 20:13:55 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int main(int argc, char **argv)
{
	t_lemin_data	data;
	(void)argv;
	(void)argc;
	if (!lemin_parse(&data))
	{
		ft_printf("[green:~] Usage:");
		return (0);
	}
	return (1);
}
