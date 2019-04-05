/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 13:05:45 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/05 16:20:43 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			lemin_vis_parse(int argc, char **argv, t_lemin_vis *vis)
{
	if (argc > 2)
	{
		ft_printf(LEMIN_ERR_OPT, argv[2]);
		return (0);
	}
	if (argc == 2 && !ft_strncmp(argv[1], "-v", -1))
	{
		ft_printf(LEMIN_ERR_OPT, argv[1]);
		return (0);
	}
	if (argc == 2)
		vis->vis = LEMIN_INPROGRESS;
	else
		vis->vis = LEMIN_NDONE;
	return (1);
}

static int	static_init_SDL2(t_lemin_vis *vis)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return (0);
	vis->win = SDL_CreateWindow(
	"lem-in", 0, 0, LEMIN_WIN_W, LEMIN_WIN_H, SDL_WINDOWPOS_CENTERED);
	if (!vis->win)
		return (0);
	vis->rend = SDL_CreateRenderer(vis->win, -1, SDL_RENDERER_ACCELERATED);
	if (!vis->rend)
		return (0);
	if (SDL_RenderSetLogicalSize(vis->rend, LEMIN_WIN_W, LEMIN_WIN_H) == -1)
		return (0);
	vis->loop = 1;
	vis->keyup.esc = 1;
	vis->keyup.h = 1;
	vis->keyup.lctrl = 1;
	vis->keyup.lshift = 1;
	vis->keyup.minus = 1;
	vis->keyup.equals = 1;
	vis->zoom = 0;
	vis->r = LEMIN_VIS_MIN_DIST;
	return (1);
}

//void	lemin_vis_mousewheel(t_lemin_vis *vis)
//{
//	if (vis->event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
//		vis->zoom++;
//	else if (vis->event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED)// && vis->zoom != 0==)
//		vis->zoom--;
//}

static void	static_handle_events(t_lemin_data *data, t_lemin_vis *vis)
{
	(void)data;

	if (vis->event.type == SDL_QUIT)
		vis->loop = 0;
	else if (vis->event.type == SDL_KEYDOWN)
		lemin_vis_keydown(vis);
	else if (vis->event.type == SDL_KEYUP)
		lemin_vis_keyup(vis);
	else
		vis->zoom = 0;
//	else if (vis->event.type == SDL_MOUSEMOTION)
//		lemin_vis_mousemotion(vis);
//	else if (vis->event.type == SDL_MOUSEBUTTONDOWN)
//		lemin_vis_mousebuttondown(vis);
//	else if (vis->event.type == SDL_MOUSEBUTTONUP)
//		lemin_vis_mousebuttonup(vis);
//	else if (vis->event.type == SDL_MOUSEWHEEL)
//		lemin_vis_mousewheel(vis);
//	else if (vis->event.type == SDL_WINDOWEVENT_FOCUS_LOST)
//		lemin_vis_focus_lost(vis);
//	else if (vis->event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
//		lemin_vis_focus_gained(vis);
}

static int	static_valid_room(t_lemin_data *data, unsigned int room)
{
	unsigned int	i;
	int				dist;
	t_lemin_node	*graph;

	graph = data->graph;
	i = room + 1;
	while (i < data->n_nodes)
	{
		dist = graph[i].x + graph[i].y - graph[room].x - graph[room].y;
		if (dist <= 5 && dist >= -5)
			return (0);
		++i;
	}
	return (1);
}

static int static_valid_coords(t_lemin_data *data)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_nodes)
	{
		if (data->graph[i].x >= LEMIN_WIN_W || data->graph[i].x < 0)
		{
			ft_printf("[redError: %s %d - %d", LEMIN_ERR_VIS1, 0, LEMIN_WIN_W);
			return (0);
		}
		if (data->graph[i].y >= LEMIN_WIN_H || data->graph[i].y < 0)
		{
			ft_printf("[redError: %s %d - %d", LEMIN_ERR_VIS2, 0, LEMIN_WIN_H);
			return (0);
		}
		if (!static_valid_room(data, i))
		{
			ft_printf("[redError: %s %d", LEMIN_ERR_VIS3, LEMIN_VIS_MIN_DIST);
			return (0);
		}
		++i;
	}
	return (1);
}

static void static_check_links(t_lemin_vis *vis, unsigned int link0,
			unsigned int link1, unsigned int *n)
{
	unsigned int i;

	i = 0;
	while (i < *n)
	{
		if ((vis->links0[i] == link0 && vis->links1[i] == link1)
		|| (vis->links0[i] == link1 && vis->links1[i] == link0))
			return ;
		++i;
	}
	vis->links0[*n] = link0;
	vis->links1[*n] = link1;
	(*n)++;
}

static void	static_fill_links(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	unsigned int	link;
	unsigned int	n;

	i = 0;
	n = 0;
	vis->links0 = ft_memalloc(sizeof(int) * data->n_links);
	vis->links1 = ft_memalloc(sizeof(int) * data->n_links);
	while (i < data->n_nodes)
	{
		link = 0;
		while (data->graph[i].links && data->graph[i].links[link])
		{
			static_check_links(vis, data->graph[i].n, data->graph[link].n, &n);
			++link;
		}
		++i;
	}
	if (n < data->n_links)
	{
		vis->links0[n] = -1;
		vis->links1[n] = -1;
	}
}

int	lemin_vis(t_lemin_data *data, t_lemin_vis *vis)
{
	if (!static_valid_coords(data))
		return (0);
	if (!static_init_SDL2(vis))
	{
		ft_printf(LEMIN_ERR, LEMIN_ERR_VIS0);
		return (0);
	}
	static_fill_links(data, vis);
	while (vis->loop)
	{
		lemin_vis_render_bg(data, vis);
		SDL_RenderPresent(vis->rend);
		SDL_WaitEvent(&vis->event);
		static_handle_events(data, vis);
	}
	return (1);
}
