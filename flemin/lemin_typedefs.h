/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/12 19:44:00 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_TYPEDEFS_H

# define LEM_IN_TYPEDEFS_H

# define LEMIN_MAX_ANTS 1000000
# define LEMIN_MAX_COORDS 100000
# define LEMIN_MIN_COORDS 0

typedef struct				s_lemin_node
{
	char					*name;
	int 					w;
	int 					ants;
	int 					value;
	long long				x;
	long long				y;
}							t_lemin_node;

typedef struct				s_lemin_way
{
	int 					*path;
	int 					len;
}							t_lemin_way;

typedef struct				s_lemin_data
{
	t_lemin_node			*graph;
	t_lemin_way				*ways;
	int 					n_ways;
	int 					node;
	int 					end;//pos of n node in array graph
	int 					start;//same for start node
	int 					link;
	char					**link0;
	char					**link1;
	char					*input;
	long long				ants;
	int 					i;
}							t_lemin_data;

#endif
