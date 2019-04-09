/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_ants.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:07:47 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 20:29:41 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_fill_delta(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	unsigned int	pos;
	unsigned int	absx;
	unsigned int	absy;

	i = 0;
	while (i < data->n_ants)
	{
		pos = data->ways[data->ants[i].w].path[data->ants[i].pos];
		absx = (UI)ft_abs(data->graph[pos].x - vis->ant_posx[i]);
		absy = (UI)ft_abs(data->graph[pos].y - vis->ant_posy[i]);
		if (absx > absy)
		{
			vis->deltax[i] = 1;
			if (!absy)
				vis->deltay[i] = 0;
			else
				vis->deltay[i] = (UI)((D)absx / (D)absy + 0.8);
		}
		else if (absx > absy)
		{
			vis->deltay[i] = 1;
			if (!absx)
				vis->deltax[i] = 0;
			vis->deltax[i] = (UI)((D)absy / (D)absx + 0.8);
		}
		else
		{
			vis->deltax[i] = 0;
			vis->deltay[i] = 0;
		}
		++i;
	}
}

void	lemin_vis_render_ants(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	n_moved;
	unsigned int	pos;
	unsigned int	n;
	unsigned int	i;

	n_moved = 1;
	n = 1;
	static_fill_delta(data, vis);
	while (n_moved)
	{
		lemin_vis_render_bg(data, vis);
		i = 0;
		n_moved = 0;
		while (i < data->n_ants)
		{
			pos = data->ways[data->ants[i].w].path[data->ants[i].pos];
			if (vis->deltax[i] != 0 && n % vis->deltax[i] == 0)
			{
				if (vis->ant_posx[i] < data->graph[pos].x)
					vis->ant_posx[i] += 1;
				else
					vis->ant_posx[i] -= 1;
			}
			if (vis->deltay[i] != 0 && n % vis->deltay[i] == 0)
			{
				if (vis->ant_posy[i] < data->graph[pos].y)
					vis->ant_posy[i] += 1;
				else
					vis->ant_posy[i] -= 1;
			}
			if ((vis->ant_posy[i] > data->graph[pos].y && vis->ant_posy[i] - data->graph[pos].y > 2)
			|| (vis->ant_posy[i] < data->graph[pos].y && data->graph[pos].y - vis->ant_posy[i] > 2)
			|| (vis->ant_posx[i] > data->graph[pos].x && vis->ant_posx[i] - data->graph[pos].x > 2)
			   || (vis->ant_posx[i] < data->graph[pos].x && data->graph[pos].x - vis->ant_posx[i] > 2))
			{
				filledEllipseRGBA(vis->rend, (Sint16)vis->ant_posx[i], (Sint16)vis->ant_posy[i],
						(Sint16)(LEMIN_VIS_SRAD_MIN + vis->zoom / 2), (Sint16)(LEMIN_VIS_SRAD_MIN + vis->zoom / 4), 100, 100, 100, 255);
				++n_moved;
			}
			++i;
		}
		SDL_RenderPresent(vis->rend);
		lemin_vis_handle_events(vis);
		if (!vis->vis)
			return ;
		++n;
	}
}
