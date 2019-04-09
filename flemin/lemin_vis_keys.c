/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:55:31 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 13:56:41 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void static_exit(t_lemin_vis *vis)
{
	if (vis->vis == 0)
		vis->vis = 1;
	else if (vis->vis == 1)
		vis->vis = 0;
}

static void	static_pause(t_lemin_vis *vis)
{
	if (vis->pause == 0)
		vis->pause = 1;
	else if (vis->pause == 1)
		vis->pause = 0;
}

void	lemin_vis_keydown(t_lemin_vis *vis)
{
	if (vis->event.key.keysym.sym == SDLK_ESCAPE)
		vis->keyup.esc = 0;
	else if (vis->event.key.keysym.sym == SDLK_SPACE)
		vis->keyup.space = 0;
}

void	lemin_vis_keyup(t_lemin_vis *vis)
{
	if (vis->event.key.keysym.sym == SDLK_ESCAPE)
	{
		vis->keyup.esc = 1;
		static_exit(vis);
	}
	else if (vis->event.key.keysym.sym == SDLK_SPACE)
	{
		vis->keyup.space = 1;
		static_pause(vis);
	}
}
