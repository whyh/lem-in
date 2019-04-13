/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_mouse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:12:37 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/13 20:53:36 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_vis_mouse_motion(t_lemin_vis *vis)
{
	if (vis->keyup.left == 0)
	{
		vis->pos_x += vis->event.motion.xrel;
		vis->pos_y += vis->event.motion.yrel;
	}
}

void	lemin_vis_mouse_buttondown(t_lemin_vis *vis)
{
	if (vis->event.button.button == SDL_BUTTON_LEFT)
		vis->keyup.left = 0;
}

void	lemin_vis_mouse_buttonup(t_lemin_vis *vis)
{
	if (vis->event.button.button == SDL_BUTTON_LEFT)
		vis->keyup.left = 1;
}

void	lemin_vis_mouse_wheel(t_lemin_vis *vis)
{
	if (vis->event.wheel.y > 0)
	{
		if (vis->min_dist - vis->zoom * 2 > LEMIN_VIS_WAY_LEN_MIN
		&& vis->moved)
			vis->zoom += LEMIN_VIS_ZOOMF;
		while (vis->min_dist - vis->zoom * 2 <= LEMIN_VIS_WAY_LEN_MIN)
			vis->zoom--;
	}
	else if (vis->event.wheel.y < 0)
	{
		if (LEMIN_VIS_ZOOMF > vis->zoom)
			vis->zoom = 0;
		else if (vis->zoom > 0 && vis->moved)
			vis->zoom -= LEMIN_VIS_ZOOMF;
	}
}
