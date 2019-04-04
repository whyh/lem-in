/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_handle_events.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:55:31 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/04 20:01:30 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_vis_keydown(t_lemin_vis *vis)
{
	if (vis->event.key.keysym.sym == SDLK_ESCAPE)
	{
		vis->keyup.esc = 0;
		vis->loop = 0;
	}
	else if (vis->event.key.keysym.sym == SDLK_LSHIFT)
		vis->keyup.lshift = 0;
	else if (vis->event.key.keysym.sym == SDLK_MINUS)
	{
		if (vis->keyup.lshift == 0 && vis->r > LEMIN_VIS_MIN_DIST)
			vis->zoom = -1;
		vis->keyup.minus = 0;
	}
	else if (vis->event.key.keysym.sym == SDLK_EQUALS)
	{
		if (vis->keyup.lshift == 0)
			vis->zoom = 1;
		vis->keyup.equals = 0;
	}
}

void	lemin_vis_keyup(t_lemin_vis *vis)
{
	if (vis->event.key.keysym.sym == SDLK_ESCAPE)
		vis->keyup.esc = 1;
	else if (vis->event.key.keysym.sym == SDLK_LSHIFT)
		vis->keyup.lshift = 1;
	else if (vis->event.key.keysym.sym == SDLK_EQUALS)
		vis->keyup.equals = 1;
	else if (vis->event.key.keysym.sym == SDLK_MINUS)
		vis->keyup.minus = 1;
}
