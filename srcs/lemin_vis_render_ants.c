/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:07:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 22:49:26 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_lemin_room	*static_get_pos(t_lemin_data *data, unsigned int i)
{
	if (data->ants[i].pos == -1)
		return (&data->graph[data->start]);
	return (&data->graph[data->ways[data->ants[i].w].path[data->ants[i].pos]]);
}

static void			static_fill_delta(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	unsigned int	dx;
	unsigned int	dy;
	t_lemin_room	*pos;

	i = 0;
	while (i < data->n_ants)
	{
		pos = static_get_pos(data, i);
		if (vis->ant_posx[i] > pos->x)
			dx = (UI)(vis->ant_posx[i] - pos->x);
		else
			dx = (UI)(pos->x - vis->ant_posx[i]);
		if (vis->ant_posy[i] > pos->y)
			dy = (UI)(vis->ant_posy[i] - pos->y);
		else
			dy = (UI)(pos->y - vis->ant_posy[i]);
		if (dx > dy && (vis->delta[i] = 'x'))
			vis->delta2[i] = (pos->y - vis->ant_posy[i]) / dx;
		else if (dy > dx && (vis->delta[i] = 'y'))
			vis->delta2[i] = (pos->x - vis->ant_posx[i]) / dy;
		++i;
	}
}

static void			static_render(t_lemin_vis *vis, unsigned int i, Sint16 rad)
{
	filledCircleRGBA(vis->rend, (Sint16)(vis->ant_posx[i] + vis->pos_x),
	(Sint16)(vis->ant_posy[i] + vis->pos_y), rad,
	R(LEMIN_RGB_ANT), G(LEMIN_RGB_ANT), B(LEMIN_RGB_ANT), 255);
	aacircleRGBA(vis->rend, (Sint16)(vis->ant_posx[i] + vis->pos_x),
	(Sint16)(vis->ant_posy[i] + vis->pos_y), rad,
	R(LEMIN_RGB_ANT), G(LEMIN_RGB_ANT), B(LEMIN_RGB_ANT), 255);
}

static int			static_move(t_lemin_vis *vis, t_lemin_room *pos,
					unsigned int i, Sint16 rad)
{
	if ((vis->delta[i] == 'x' && vis->ant_posx[i] != pos->x)
	|| (vis->delta[i] == 'y' && vis->ant_posy[i] != pos->y))
	{
		if (vis->delta[i] == 'x' && vis->ant_posx[i] != pos->x)
		{
			if (vis->ant_posx[i] < pos->x)
				vis->ant_posx[i]++;
			else
				vis->ant_posx[i]--;
			vis->ant_posy[i] += vis->delta2[i];
		}
		if (vis->delta[i] == 'y' && vis->ant_posy[i] != pos->y)
		{
			if (vis->ant_posy[i] < pos->y)
				vis->ant_posy[i]++;
			else
				vis->ant_posy[i]--;
			vis->ant_posx[i] += vis->delta2[i];
		}
		static_render(vis, i, rad);
		return (1);
	}
	pos->way = 1;
	return (0);
}

int					lemin_vis_render_ants(t_lemin_data *data, t_lemin_vis *vis,
					unsigned int move)
{
	unsigned int	moved;
	t_lemin_room	*pos;
	unsigned int	i;
	Sint16			rad;

	rad = (Sint16)((LEMIN_VIS_SRAD_MIN + vis->zoom) / 2);
	static_fill_delta(data, vis);
	moved = 0;
	i = 0;
	while (i < data->n_ants)
	{
		pos = static_get_pos(data, i);
		if (move)
		{
			if (static_move(vis, pos, i, rad))
				++moved;
			else if (vis->delta[i] == 'y' || vis->delta[i] == 'x')
				pos->value = 1;
		}
		else
			static_render(vis, i, rad);
		++i;
	}
	return (moved);
}
