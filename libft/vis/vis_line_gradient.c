/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_line_gradient.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 19:56:44 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/10 20:05:43 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static Uint8	static_get_color(int rgb0, int rgb1, double pct)
{
	return ((Uint8)(pct * rgb1 + rgb0 * (1 - pct)));
}

static double	static_gradient_pct(int coord, int coord0, int coord1)
{
	double	pos;
	double	pct;
	double	dist;

	dist = coord1 - coord0;
	pos = coord - coord0;
	if (dist == 0)
		pct = 1.0;
	else
		pct = pos / dist;
	return (pct);
}

void			ft_line_gradient(t_vis_process_line *pl, t_vis_rgba *color)
{
	double	pct;

	pct = static_gradient_pct((int)pl->x, (int)pl->x0, (int)pl->x1);
	color->r = static_get_color(pl->rgb0 >> 16, pl->rgb1 >> 16, pct);
	color->g = static_get_color((pl->rgb0 >> 8) & 255, (pl->rgb1 >> 8) & 255, pct);
	color->b = static_get_color((pl->rgb0) & 255, (pl->rgb1) & 255, pct);
}