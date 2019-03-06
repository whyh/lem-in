/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in_typedefs.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/06 21:47:12 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_TYPEDEFS_H

# define LEM_IN_TYPEDEFS_H

typedef struct				s_lemin_node
{
	char					*name;
	int						x;
	int						y;
	int						n;//of connections
	struct	s_lemin_node	**pos_prev;
	struct	s_lemin_node	**pos_parallel;
	struct	s_lemin_node	**pos_next;
	struct	s_lemin_node	*next;
}							t_lemin_node;

typedef struct				s_lemin_data
{
	t_lemin_node			*graph;
	t_lemin_node			*start_node;
	t_lemin_node			*end_node;
	char					*input;
	int						nodes;//of ellements
	int						ants;
}							t_lemin_data;

typedef struct				s_lemin_parse
{
	t_lemin_node			*node;
	t_lemin_head			*head;
	char					*buff;
	int 					start;
	int 					end;
	int 					start_next;
	int 					end_next;
}							t_lemin_parse;

#endif
