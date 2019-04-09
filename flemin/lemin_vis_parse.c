/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 14:05:27 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 19:26:48 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int	static_valid_coords(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	i;
	unsigned int	dist;
	unsigned int	room;

	room = 0;
	while (room < data->n_nodes)
	{
		i = room + 1;
		while (i < data->n_nodes)
		{
			dist = (UI)ft_abs(data->graph[i].x - data->graph[room].x)
			+ (UI)ft_abs(data->graph[i].y - data->graph[room].y);
			if (dist <= LEMIN_VIS_MIN_DIST)
			{
				ft_printf(LEMIN_ERR_DIST, LEMIN_ERR_VIS3, LEMIN_VIS_MIN_DIST);
				return (0);
			}
			if (dist < vis->min_dist || !vis->min_dist)
				vis->min_dist = dist;
			++i;
		}
		++room;
	}
	vis->min_dist = vis->min_dist / 3 * 2;
	return (1);
}

static void	static_store(t_lemin_vis *vis, unsigned int link0,
			unsigned int link1)
{
	unsigned int		i;
	static unsigned int	n = 0;

	i = 0;
	while (i < n)
	{
		if ((vis->links0[i] == link0 && vis->links1[i] == link1)
		|| (vis->links1[i] == link0 && vis->links0[i] == link1))
			return ;
		++i;
	}
	vis->links0[n] = link0;
	vis->links1[n] = link1;
	++n;
}

static void	static_fill_links_n_rad(t_lemin_data *data, t_lemin_vis *vis)
{
	unsigned int	room;
	unsigned int	link;

	room = 0;
	while (room < data->n_nodes)
	{
		link = 0;
		while (data->graph[room].links && data->graph[room].links[link])
		{
			static_store(vis, room, data->graph[room].links[link]->n);
			++link;
		}
		if (room == data->start || room == data->end)
			data->graph[room].rad = LEMIN_VIS_BRAD_MIN;
		else
			data->graph[room].rad = LEMIN_VIS_SRAD_MIN;
		++room;
	}
}

static void	static_init(t_lemin_data *data, t_lemin_vis *vis)
{
	vis->links0 = ft_memalloc(sizeof(int) * (data->n_links + 1));
	vis->links1 = ft_memalloc(sizeof(int) * (data->n_links + 1));
	vis->ant_posx = ft_memalloc(sizeof(int) * data->n_ants);
	vis->ant_posy = ft_memalloc(sizeof(int) * data->n_ants);
	vis->deltax = ft_memalloc(sizeof(int) * data->n_ants);
	vis->deltay = ft_memalloc(sizeof(int) * data->n_ants);
	vis->min_dist = 0;
	vis->pause = 1;
	vis->zoom = LEMIN_VIS_START_ZOOM;
	vis->prev_zoom = 0;
	vis->prev_posy = 0;
	vis->prev_posx = 0;
	vis->pos_x = 0;
	vis->pos_y = 0;
	vis->keyup.esc = 1;
	vis->keyup.h = 1;
	vis->keyup.space = 1;
	vis->keyup.left = 1;
}

int			lemin_vis_parse(t_lemin_data *data, t_lemin_vis *vis, int argc,
			char **argv)
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
	if (argc == 1)
		vis->vis = 0;
	else
	{
		vis->vis = 1;
		static_init(data, vis);
		if (!static_valid_coords(data, vis))
			return (0);
		static_fill_links_n_rad(data, vis);
	}
	return (1);
}
