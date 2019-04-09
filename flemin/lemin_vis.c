/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:05:45 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/09 17:18:20 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_init_SDL2(t_lemin_vis *vis)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (0);
	vis->win = SDL_CreateWindow(LEMIN_VIS_WIN_NAME, 0, 0, LEMIN_WIN_W,
	LEMIN_WIN_H, SDL_WINDOWPOS_CENTERED);
	if (!vis->win)
		return (0);
	vis->rend = SDL_CreateRenderer(vis->win, -1, SDL_RENDERER_ACCELERATED);
	if (!vis->rend)
		return (0);
	if (SDL_RenderSetLogicalSize(vis->rend, LEMIN_WIN_W, LEMIN_WIN_H) == -1)
		return (0);
	return (1);
}

void		lemin_vis_handle_events(t_lemin_vis *vis)
{
	SDL_WaitEvent(&vis->event);
	if (vis->event.type == SDL_QUIT)
		vis->vis = 0;
	else if (vis->event.type == SDL_KEYDOWN)
		lemin_vis_keydown(vis);
	else if (vis->event.type == SDL_KEYUP)
		lemin_vis_keyup(vis);
	else if (vis->event.type == SDL_MOUSEMOTION)
		lemin_vis_mouse_motion(vis);
	else if (vis->event.type == SDL_MOUSEBUTTONDOWN)
		lemin_vis_mouse_buttondown(vis);
	else if (vis->event.type == SDL_MOUSEBUTTONUP)
		lemin_vis_mouse_buttonup(vis);
	else if (vis->event.type == SDL_MOUSEWHEEL)
		lemin_vis_mouse_wheel(vis);
//	else if (vis->event.type == SDL_WINDOWEVENT_FOCUS_LOST)
//		lemin_vis_focus_lost(vis);
//	else if (vis->event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
//		lemin_vis_focus_gained(vis);
}

int			lemin_vis(t_lemin_data *data, t_lemin_vis *vis)
{
	if (!static_init_SDL2(vis))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_VIS0);
		return (0);
	}
	while (vis->vis)
	{
		if (!vis->pause)
		{
			if (!lemin_move_ants_turn(data, vis))
				vis->pause = 1;
			lemin_vis_render_ants(data, vis);
		}
		lemin_vis_render_bg(data, vis);
		SDL_RenderPresent(vis->rend);
		vis->prev_zoom = vis->zoom;
		vis->prev_posx = vis->pos_x;
		vis->prev_posy = vis->pos_y;
		lemin_vis_handle_events(vis);
	}
	return (1);
}
