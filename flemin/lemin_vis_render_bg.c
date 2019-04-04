/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_bg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:40:34 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/04 21:11:04 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"


void	static_render_links(t_lemin_data *data, t_lemin_vis *vis, unsigned int room)
{
	unsigned int	i;
	SDL_Point		p0;
	SDL_Point		p1;

	i = 0;
	p0.x = data->graph[room].x + vis->r;
	p0.y = data->graph[room].y;//TODO create array of links
	while (data->graph[room].links && data->graph[room].links[i])//TODO depending on the direction plus or minus r
	{
		p1.x = data->graph[room].links[i]->x + vis->r;
		p1.y = data->graph[room].links[i]->y;
		aalineRGBA(vis->rend, (Sint16)p0.x, (Sint16)p0.y, (Sint16)p1.x, (Sint16)p1.y, 10, 10, 10, 255);
		++i;
	}
}

void	static_render_graph(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int		i;

	i = 0;
	vis->r += vis->zoom;
	while (i < data->n_nodes)//TODO draw links then rooms
	{
		if (data->graph[i].x > LEMIN_WIN_W / 2)
			data->graph[i].x += vis->zoom * 2;
		else if (data->graph[i].x < LEMIN_WIN_W / 2)
			data->graph[i].x -= vis->zoom * 2;
		if (data->graph[i].y > LEMIN_WIN_H / 2)
			data->graph[i].y += vis->zoom * 2;
		else if (data->graph[i].y < LEMIN_WIN_H / 2)
			data->graph[i].y -= vis->zoom * 2;
		static_render_links(data, vis, i);
		aacircleRGBA(vis->rend, (Sint16)data->graph[i].x, (Sint16)data->graph[i].y, (Sint16)vis->r, 100, 255, 100, 255);
		filledCircleRGBA(vis->rend, (Sint16)data->graph[i].x, (Sint16)data->graph[i].y, (Sint16)vis->r, 100, 255, 100, 255);
		aacircleRGBA(vis->rend, (Sint16)data->graph[i].x, (Sint16)data->graph[i].y, (Sint16)vis->r, 100, 100, 100, 255);
		++i;
	}
}

void	lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis)
{
	SDL_SetRenderDrawColor(vis->rend, 100, 255, 100, 255);
	SDL_RenderClear(vis->rend);
	static_render_graph(data, vis);
}
