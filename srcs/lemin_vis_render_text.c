/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_render_text.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 22:13:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 23:05:32 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_render_counter(t_lemin_vis *vis)
{
	t_lemin_vis_text	counter;
	char				*digit;
	char				*text;

	if (!(counter.font = TTF_OpenFont("lato/Lato-Regular.ttf", 60)))
		return ;
	counter.color.a = 255;
	counter.color.r = R(LEMIN_RGB_COUNTER);
	counter.color.g = G(LEMIN_RGB_COUNTER);
	counter.color.b = B(LEMIN_RGB_COUNTER);
	text = ft_strndup(LEMIN_COUNTER_TEXT, -1);
	digit = ft_itoabase(DEC, vis->turns);
	ft_strninject(&text, digit, -1, -1);
	ft_strdel(&digit);
	counter.surface = TTF_RenderText_Solid(counter.font, text, counter.color);
	ft_strdel(&text);
	counter.texture = SDL_CreateTextureFromSurface(vis->rend, counter.surface);
	counter.box.x = LEMIN_COUNTER_X;
	counter.box.y = LEMIN_COUNTER_Y;
	counter.box.w = LEMIN_COUNTER_W;
	counter.box.h = LEMIN_COUNTER_H;
	SDL_RenderCopy(vis->rend, counter.texture, NULL, &counter.box);
	SDL_DestroyTexture(counter.texture);
	SDL_FreeSurface(counter.surface);
}

void		lemin_vis_render_text(t_lemin_vis *vis)
{
	if (vis->counter)
		static_render_counter(vis);
}
