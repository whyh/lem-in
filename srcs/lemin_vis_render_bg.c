/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_bg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:40:34 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 23:00:56 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_adapt_coords(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_rooms)
	{
		if (data->graph[i].y > LEMIN_VIS_WIN_H / 2)
			data->graph[i].y += (vis->zoom - vis->prev_zoom) * 2;
		else if (data->graph[i].y < LEMIN_VIS_WIN_H / 2)
			data->graph[i].y -= (vis->zoom - vis->prev_zoom) * 2;
		if (data->graph[i].x > LEMIN_VIS_WIN_W / 2)
			data->graph[i].x += (vis->zoom - vis->prev_zoom) * 2;
		else if (data->graph[i].x < LEMIN_VIS_WIN_W / 2)
			data->graph[i].x -= (vis->zoom - vis->prev_zoom) * 2;
		data->graph[i].rad += (vis->zoom - vis->prev_zoom);
		++i;
	}
}

static void	static_render_links(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	t_vis_line		line;

	i = 0;
	while (vis->links0[i] != 0 || vis->links1[i] != 0)
	{
		line.x0 = (Sint16)(data->graph[vis->links0[i]].x + vis->pos_x);
		line.x1 = (Sint16)(data->graph[vis->links1[i]].x + vis->pos_x);
		line.y0 = (Sint16)(data->graph[vis->links0[i]].y + vis->pos_y);
		line.y1 = (Sint16)(data->graph[vis->links1[i]].y + vis->pos_y);
		line.rend = vis->rend;
		line.opacity = 255;
		line.rgb0 = LEMIN_RGB_LINK;
		line.rgb1 = LEMIN_RGB_LINK;
		line.thikness = 1;
		ft_aaline(&line);
		line.x0 = (Sint16)(data->graph[vis->links0[i]].x + vis->pos_x - 1);
		line.x1 = (Sint16)(data->graph[vis->links1[i]].x + vis->pos_x - 1);
		line.y0 = (Sint16)(data->graph[vis->links0[i]].y + vis->pos_y - 1);
		line.y1 = (Sint16)(data->graph[vis->links1[i]].y + vis->pos_y - 1);
		ft_aaline(&line);
		line.x0 = (Sint16)(data->graph[vis->links0[i]].x + vis->pos_x + 1);
		line.x1 = (Sint16)(data->graph[vis->links1[i]].x + vis->pos_x + 1);
		line.y0 = (Sint16)(data->graph[vis->links0[i]].y + vis->pos_y + 1);
		line.y1 = (Sint16)(data->graph[vis->links1[i]].y + vis->pos_y + 1);
		ft_aaline(&line);
		++i;
	}
}

static void	static_render_rooms(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	Sint16			x;
	Sint16			y;

	i = 0;
	while (i < data->n_rooms)
	{
		x = (Sint16)(data->graph[i].x + vis->pos_x);
		y = (Sint16)(data->graph[i].y + vis->pos_y);
		if (data->graph[i].way)
			filledCircleRGBA(vis->rend, x, y, (Sint16)data->graph[i].rad,
			R(LEMIN_RGB_ANT), G(LEMIN_RGB_ANT), B(LEMIN_RGB_ANT), 255);
		else
			filledCircleRGBA(vis->rend, x, y, (Sint16)data->graph[i].rad,
			R(LEMIN_RGB_BG), G(LEMIN_RGB_BG), B(LEMIN_RGB_BG), 255);
		aacircleRGBA(vis->rend, x, y, (Sint16)(data->graph[i].rad),
		R(LEMIN_RGB_BORDER), G(LEMIN_RGB_BORDER), B(LEMIN_RGB_BORDER), 255);
		aacircleRGBA(vis->rend, x, y, (Sint16)(data->graph[i].rad - 1),
		R(LEMIN_RGB_BORDER), G(LEMIN_RGB_BORDER), B(LEMIN_RGB_BORDER), 255);
		aacircleRGBA(vis->rend, x, y, (Sint16)(data->graph[i].rad - 2),
		R(LEMIN_RGB_BORDER), G(LEMIN_RGB_BORDER), B(LEMIN_RGB_BORDER), 255);
		aacircleRGBA(vis->rend, x, y, (Sint16)(data->graph[i].rad - 3),
		R(LEMIN_RGB_BORDER), G(LEMIN_RGB_BORDER), B(LEMIN_RGB_BORDER), 255);
		++i;
	}
}

void		lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis)
{
	SDL_SetRenderDrawColor(vis->rend,
	R(LEMIN_RGB_BG), G(LEMIN_RGB_BG), B(LEMIN_RGB_BG), 255);
	SDL_RenderClear(vis->rend);
	if (vis->zoom != vis->prev_zoom)
		static_adapt_coords(data, vis);
	static_render_links(data, vis);
	static_render_rooms(data, vis);
}
