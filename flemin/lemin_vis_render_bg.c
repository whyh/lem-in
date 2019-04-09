/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_bg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:40:34 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 19:04:37 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_adapt_coords(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_nodes)
	{
		data->graph[i].x += (vis->pos_x - vis->prev_posx);
		data->graph[i].y += (vis->pos_y - vis->prev_posy);
		if (data->graph[i].y > LEMIN_WIN_H / 2)
			data->graph[i].y += (vis->zoom - vis->prev_zoom) * 2;
		else if (data->graph[i].y < LEMIN_WIN_H / 2)
			data->graph[i].y -= (vis->zoom - vis->prev_zoom) * 2;
		if (data->graph[i].x > LEMIN_WIN_W / 2)
			data->graph[i].x += (vis->zoom - vis->prev_zoom) * 2;
		else if (data->graph[i].x < LEMIN_WIN_W / 2)
			data->graph[i].x -= (vis->zoom - vis->prev_zoom) * 2;
		data->graph[i].rad += (vis->zoom - vis->prev_zoom);
		++i;
	}
}

static void	static_render_links(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	Sint16			x0;
	Sint16			x1;
	Sint16			y0;
	Sint16			y1;

	i = 0;
	while (vis->links0[i] != 0 || vis->links1[i] != 0)
	{
		x0 = (Sint16)data->graph[vis->links0[i]].x;
		x1 = (Sint16)data->graph[vis->links1[i]].x;
		y0 = (Sint16)data->graph[vis->links0[i]].y;
		y1 = (Sint16)data->graph[vis->links1[i]].y;
		aalineRGBA(vis->rend, x0, y0, x1, y1, 100, 100, 100, 255);
		aalineRGBA(vis->rend, (Sint16)(x0 - 1), (Sint16)(y0 - 1), (Sint16)(x1 - 1), (Sint16)(y1 - 1), 100, 100, 100, 255);
		aalineRGBA(vis->rend, (Sint16)(x0 + 1), (Sint16)(y0 + 1), (Sint16)(x1 + 1), (Sint16)(y1 + 1), 100, 100, 100, 255);
		++i;
	}
}

static void	static_render_rooms(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	Sint16			x;
	Sint16			y;
	Sint16			rad;

	i = 0;
	while (i < data->n_nodes)
	{
		x = (Sint16)data->graph[i].x;
		y = (Sint16)data->graph[i].y;
		rad = (Sint16)data->graph[i].rad;
		filledCircleRGBA(vis->rend, x, y, (Sint16)(rad - 1), 10, 100, 10, 255);
		if (data->graph[i].ant)
			filledCircleRGBA(vis->rend, x, y, rad, 100, 100, 100, 255);
		aacircleRGBA(vis->rend, x, y, rad, 255, 255, 255, 255);
		++i;
	}
}

void	lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis)
{
	SDL_SetRenderDrawColor(vis->rend, 10, 100, 10, 255);
	SDL_RenderClear(vis->rend);
	static_adapt_coords(data, vis);
	static_render_links(data, vis);
	static_render_rooms(data, vis);
}

