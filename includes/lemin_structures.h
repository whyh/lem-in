/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_structures.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 22:43:52 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_STRUCTURES_H

# define LEMIN_STRUCTURES_H

typedef struct				s_lemin_input
{
	char					*buff;
	struct s_lemin_input	*next;
}							t_lemin_input;

typedef struct				s_lemin_parse
{
	t_lemin_input			*input;
	unsigned int			line;
	unsigned int			ants : 2;
	unsigned int			rooms : 2;
	unsigned int			start : 2;
	unsigned int			end : 2;
}							t_lemin_parse;

typedef struct				s_lemin_room
{
	char					*name;
	int						x;
	int						y;
	int						rad;
	int						ant;
	unsigned int			n;
	unsigned int			value;
	unsigned int			way;
	unsigned int			n_links;
	struct s_lemin_room		**links;
}							t_lemin_room;

typedef struct				s_lemin_way
{
	unsigned int			*path;
	unsigned int			n_ants;
	unsigned int			len;
}							t_lemin_way;

typedef struct				s_lemin_ant
{
	unsigned int			n;
	unsigned int			w;
	int						pos;
}							t_lemin_ant;

typedef struct				s_lemin_data
{
	t_lemin_room			*graph;
	t_lemin_way				*ways;
	t_lemin_ant				*ants;
	unsigned int			n_rooms;
	unsigned int			n_links;
	unsigned int			n_ants;
	unsigned int			n_ways;
	unsigned int			end;
	unsigned int			start;
}							t_lemin_data;

#endif
