/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:39:49 by danial            #+#    #+#             */
/*   Updated: 2019/04/14 23:38:07 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_free_vis(t_lemin_vis *vis)
{
	if (vis->rend)
		SDL_DestroyRenderer(vis->rend);
	if (vis->win)
		SDL_DestroyWindow(vis->win);
	if (vis->links0)
		ft_memdel((void**)(&vis->links0));
	if (vis->links1)
		ft_memdel((void**)(&vis->links1));
	if (vis->ant_posx)
		ft_memdel((void**)(&vis->ant_posx));
	if (vis->ant_posy)
		ft_memdel((void**)(&vis->ant_posy));
	if (vis->delta)
		ft_memdel((void**)(&vis->delta));
	if (vis->delta2)
		ft_memdel((void**)(&vis->delta2));
}

static void	static_free_input(t_lemin_input *input)
{
	t_lemin_input	*prev;

	if (input->buff)
		ft_strdel(&input->buff);
	if (input->next)
	{
		input = input->next;
		while (input)
		{
			if (input->buff)
				ft_strdel(&input->buff);
			prev = input;
			input = input->next;
			ft_memdel((void**)(&prev));
		}
	}
}

static void	static_free_data(t_lemin_data *data)
{
	unsigned int	i;

	if (data->graph)
	{
		i = 0;
		while (i < data->n_rooms && data->graph[i].name)
		{
			if (data->graph[i].name)
				ft_strdel(&(data->graph[i].name));
			if (data->graph[i].links)
				ft_memdel((void**)(&data->graph[i].links));
			++i;
		}
		ft_memdel((void**)(&data->graph));
	}
	if (data->ants)
		ft_memdel((void**)(&data->ants));
	if (data->ways)
	{
		i = 0;
		while (i < data->n_ways)
			ft_memdel((void**)(&data->ways[i++].path));
	}
}

void		lemin_exit(t_lemin_data *data, t_lemin_input *input,
			t_lemin_vis *vis)
{
	static_free_data(data);
	static_free_input(input);
	if (vis->vis)
		static_free_vis(vis);
}
