/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aaline_thin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:49:58 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/13 16:14:44 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vis.h"

static void	static_draw_p(t_vis_process_line *pl, int x, int y, double sat)
{
	t_vis_rgba	color;

	if (sat <= 0.3)
		sat += 0.1;
	ft_line_gradient(pl, &color);
	color.a = (Uint8)(pl->opacity * sat);
	SDL_SetRenderDrawColor(pl->rend, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(pl->rend, x, y);
}

static void	static_init_line(t_vis_process_line *pl)
{
	double	dx;
	double	dy;

	dx = pl->x1 - pl->x0;
	if (pl->x0 > pl->x1)
		dx = pl->x0 - pl->x1;
	dy = pl->y1 - pl->y0;
	if (pl->y0 > pl->y1)
		dy = pl->y0 - pl->y1;
	if (dy > dx)
	{
		ft_swap_d(&(pl->y0), &(pl->x0));
		ft_swap_d(&(pl->y1), &(pl->x1));
		pl->reversed = 1;
		static_draw_p(pl, (int)pl->y0, (int)pl->x0, 1 - pl->y0 + (int)pl->y0);
		static_draw_p(pl, (int)pl->y1 + 1, (int)pl->x1, pl->y1 - (int)pl->y1);
	}
	else
	{
		static_draw_p(pl, (int)pl->x0, (int)pl->y0, 1 - pl->x0 + (int)pl->x0);
		static_draw_p(pl, (int)pl->x1 + 1, (int)pl->y1, pl->x1 - (int)pl->x1);
	}
	if (pl->x1 < pl->x0)
	{
		ft_swap_d(&(pl->x0), &(pl->x1));
		ft_swap_d(&(pl->y0), &(pl->y1));
	}
	dx = pl->x1 - pl->x0;
	dy = pl->y1 - pl->y0;
	pl->d = dy / dx;
}

static void	static_fill(t_vis_line *line, t_vis_process_line *pl)
{
	pl->rend = line->rend;
	pl->x0 = (D)line->x0;
	pl->y0 = (D)line->y0;
	pl->x1 = (D)line->x1;
	pl->y1 = (D)line->y1;
	pl->rgb0 = line->rgb0;
	pl->rgb1 = line->rgb1;
	pl->opacity = line->opacity;
	pl->reversed = 0;
}

void		ft_aaline_thin(t_vis_line *line)
{
	t_vis_process_line	pl;

	static_fill(line, &pl);
	SDL_SetRenderDrawBlendMode(pl.rend, SDL_BLENDMODE_BLEND);
	static_init_line(&pl);
	pl.x = (int)pl.x0 + 1;
	pl.y = (int)pl.y0;
	while (pl.x <= pl.x1)
	{
		if (pl.reversed == 0)
		{
			static_draw_p(&pl, (int)pl.x, (int)pl.y, 1 - (pl.y - (int)pl.y));
			static_draw_p(&pl, (int)pl.x, (int)pl.y + 1, pl.y - (int)pl.y);
		}
		else if (pl.reversed == 1)
		{
			static_draw_p(&pl, (int)pl.y, (int)pl.x, 1 - (pl.y - (int)pl.y));
			static_draw_p(&pl, (int)pl.y + 1, (int)pl.x, pl.y - (int)pl.y);
		}
		pl.x++;
		pl.y += pl.d;
	}
}
