/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/21 15:19:46 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_TYPEDEFS_H

# define LEM_IN_TYPEDEFS_H

# define LEMIN_MAX_ANTS 1000000
# define LEMIN_MAX_ROOMS 1000000
# define LEMIN_MAX_WAYS LEMIN_MAX_ROOMS
# define LEMIN_MAX_VALUE LEMIN_MAX_ROOMS
# define LEMIN_UNSPEC LEMIN_MAX_ROOMS + 1
# define LEMIN_BEING_SPEC LEMIN_MAX_ROOMS + 2
# define LEMIN_MAX_COORDS 100000
# define LEMIN_MIN_COORDS -100000

typedef struct				s_lemin_node
{
	char					*name;
	int						x;
	int						y;
	unsigned int 			n;
	unsigned int			value;
	unsigned int			w;
	unsigned int 			n_links;
	struct s_lemin_node		**links;
}							t_lemin_node;

typedef struct				s_lemin_way
{
	unsigned int 			*path;
	unsigned int			n_ants;
	unsigned int 			len;
}							t_lemin_way;

typedef struct				s_lemin_ant
{
	unsigned int			n;
	unsigned int			w;
	int						pos;//in the way array
}							t_lemin_ant;

typedef struct				s_lemin_data
{
	t_lemin_node			*graph;
	t_lemin_way				*ways;
	t_lemin_ant				*ants;
	unsigned int			n_ways;
	unsigned int			n_nodes;
	unsigned int			n_links;
	unsigned int			end;
	unsigned int			start;
	unsigned int			n_ants;
	char					*input;//TODO rm from structure
	unsigned int			i;
}							t_lemin_data;

#endif
