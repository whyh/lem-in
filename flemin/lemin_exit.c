/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danial <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:39:49 by danial            #+#    #+#             */
/*   Updated: 2019/04/11 18:39:49 by danial           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	static_free_vis(t_lemin_vis *vis)
{
	SDL_DestroyRenderer(vis->rend);
	SDL_DestroyWindow(vis->win);
	ft_memdel((void**)(&vis->links0));
	ft_memdel((void**)(&vis->links1));
	ft_memdel((void**)(&vis->ant_posx));
	ft_memdel((void**)(&vis->ant_posy));
	ft_memdel((void**)(&vis->deltax));
	ft_memdel((void**)(&vis->deltay));
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

static void	static_free_solutions(t_lemin_solution *solution)
{
	unsigned int	i;

	if (solution->ants)
		ft_memdel((void**)(&solution->ants));
	if (solution->ways)
	{
		i = 0;
		while (i < solution->n_ways)
		{
			ft_memdel((void **)(&solution->ways[i].path));
			++i;
		}
		ft_memdel((void **)(&solution->ways));
	}
	solution->turns = 0;
	solution->n_ways = 0;
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
	i = 0;
	while (i < LEMIN_MAX_SOLUTIONS && data->solutions[i].turns)
	{
		static_free_solutions(&data->solutions[i]);
		++i;
	}
}

void		lemin_exit(t_lemin_data *data, t_lemin_input *input,
			t_lemin_vis *vis)
{
	static_free_data(data);
	static_free_input(input);
	static_free_vis(vis);
}
