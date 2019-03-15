/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/15 14:46:20 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_TYPEDEFS_H

# define LEM_IN_TYPEDEFS_H

# define LEMIN_MAX_ANTS 1000000
# define LEMIN_UNSPEC -1
# define LEMIN_BEING_SPEC -2
# define LEMIN_MAX_COORDS 100000
# define LEMIN_MIN_COORDS -100000

typedef struct				s_lemin_node
{
	char					*name;
	int 					n;
	int 					w;
	int 					n_links;
	int 					n_ants;
	int 					value;
	long long				x;
	long long				y;
	struct s_lemin_node		**links;
}							t_lemin_node;

typedef struct				s_lemin_way
{
	int 					*path;
	int 					*p_ant;
	int						ants;
	int 					len;
}							t_lemin_way;

typedef struct				s_lemin_ant
{
	int 					n;
	int 					w;
	int 					pos;
}							t_lemin_ant;

typedef struct				s_lemin_data
{
	t_lemin_node			*graph;
	t_lemin_way				*ways;
	t_lemin_ant				*ants_arr;
	int 					n_ways;
	int 					n_nodes;
	int 					n_links;
	int 					end;
	int 					start;
	char					*input;
	long long				ants;
	int 					i;
}							t_lemin_data;

#endif
