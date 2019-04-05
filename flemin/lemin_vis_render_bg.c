/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_bg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:40:34 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/05 17:15:10 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	static_render_links(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	SDL_Point		p0;
	SDL_Point		p1;

	i = 0;
	while (vis->links0[i] != -1)
	{
		p0.x = data->graph[vis->links0[i]].x;
		p0.y = data->graph[vis->links0[i]].y;
		p1.x = data->graph[vis->links1[i]].x;
		p1.y = data->graph[vis->links1[i]].y
		if (p0.x > p1.x)
		{
			p0.x -= vis->r;
			p1.x += vis->r;
		}
		else
		{
			p0.x += vis->r;
			p1.x -= vis->r;
		}
		if (p0.y > p1.y)
		{
			p0.y -= vis->r;
			p1.y += vis->r;
		}
		else
		{
			p0.y += vis->r;
			p1.y -= vis->r;
		}
		if ((p0.x >= 0 && p0.x <= LEMIN_WIN_W && p0.y >= 0 && p0.y <= LEMIN_WIN_H)
		|| (p1.x >= 0 && p1.x <= LEMIN_WIN_W && p1.y >= 0 && p1.y <= LEMIN_WIN_H))
			aalineRGBA(vis->rend, (Sint16)p0.x, (Sint16)p0.y,
					(Sint16)p1.x, (Sint16)p1.y, 10, 10, 10, 255);
		++i;
	}
}

void	static_render_rooms(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;

	i = 0;
	vis->r += vis->zoom;
	while (i < data->n_nodes)
	{
		if (data->graph[i].x > LEMIN_WIN_W / 2)
			data->graph[i].x += vis->zoom * 2;
		else if (data->graph[i].x < LEMIN_WIN_W / 2)
			data->graph[i].x -= vis->zoom * 2;
		if (data->graph[i].y > LEMIN_WIN_H / 2)
			data->graph[i].y += vis->zoom * 2;
		else if (data->graph[i].y < LEMIN_WIN_H / 2)
			data->graph[i].y -= vis->zoom * 2;
		if (data->graph[i].x >= 0 && data->graph[i].x <= LEMIN_WIN_W
		&& data->graph[i].y >= 0 && data->graph[i].y <= LEMIN_WIN_H)
			aacircleRGBA(vis->rend, (Sint16)data->graph[i].x,
			(Sint16)data->graph[i].y, (Sint16)vis->r, 100, 100, 100, 255);
		++i;
	}
}

void	lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis)
{
	SDL_SetRenderDrawColor(vis->rend, 100, 255, 100, 255);
	SDL_RenderClear(vis->rend);
	static_render_rooms(data, vis);
	static_render_links(data, vis);
}
