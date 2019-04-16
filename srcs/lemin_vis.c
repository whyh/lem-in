/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:05:45 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 23:51:48 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_init_sdl2(t_lemin_vis *vis)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (0);
	if (TTF_Init() == -1)
		return (0);
	vis->win = SDL_CreateWindow(LEMIN_VIS_WIN_NAME, 0, 0, LEMIN_VIS_WIN_W,
	LEMIN_VIS_WIN_H, SDL_WINDOW_SHOWN);
	if (!vis->win)
		return (0);
	vis->rend = SDL_CreateRenderer(vis->win, -1, SDL_RENDERER_ACCELERATED);
	if (!vis->rend)
		return (0);
	if (SDL_RenderSetLogicalSize(vis->rend, LEMIN_VIS_WIN_W, LEMIN_VIS_WIN_H)
	== -1)
		return (0);
	return (1);
}

static void	static_handle_events(t_lemin_vis *vis)
{
	vis->prev_zoom = vis->zoom;
	if (!SDL_WaitEventTimeout(&vis->event, 0))
		return ;
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
}

static void	static_wait(t_lemin_data *data, t_lemin_vis *vis, unsigned int s)
{
	struct timeval	t1;
	struct timeval	t2;

	gettimeofday(&t1, NULL);
	t2.tv_sec = t1.tv_sec;
	while (t2.tv_sec - t1.tv_sec < s)
	{
		lemin_vis_render_bg(data, vis);
		lemin_vis_render_text(vis);
		SDL_RenderPresent(vis->rend);
		static_handle_events(vis);
		gettimeofday(&t2, NULL);
	}
}

static void	static_run(t_lemin_data *data, t_lemin_vis *vis)
{
	if (vis->moved)
	{
		lemin_set_way(data, 0);
		if (!lemin_move_ants_turn(data, vis))
			vis->pause = 1;
		else
			vis->turns++;
		vis->moved = 0;
	}
	if (!lemin_vis_render_ants(data, vis, 1))
	{
		vis->moved = 1;
		static_wait(data, vis, LEMIN_S_BTW_TURNS);
	}
}

int			lemin_vis(t_lemin_data *data, t_lemin_vis *vis)
{
	if (!static_init_sdl2(vis))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_VIS0);
		return (0);
	}
	while (vis->vis)
	{
		lemin_vis_render_bg(data, vis);
		if (vis->pause && !vis->moved)
			lemin_vis_render_ants(data, vis, 0);
		else if (!vis->pause)
			static_run(data, vis);
		lemin_vis_render_text(vis);
		SDL_RenderPresent(vis->rend);
		static_handle_events(vis);
	}
	vis->vis = 1;
	SDL_Quit();
	TTF_Quit();
	return (1);
}
