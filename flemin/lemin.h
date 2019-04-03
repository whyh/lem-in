/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:33 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/03 21:04:55 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "../libft/libft.h"
# include "lemin_typedefs.h"

int		lemin_parse(t_lemin_data *data, t_lemin_input *input);
int		lemin_parse_ants(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);
int		lemin_parse_rooms(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);
int		lemin_parse_links(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);

int 	lemin_find_way(t_lemin_data *data);
void	lemin_split_ants(t_lemin_data *data);
void	lemin_move_ants(t_lemin_data *data);

int		lemin_valid_room(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);

int		lemin_set_way(t_lemin_data *data, unsigned int way_n);
int		lemin_set_value(t_lemin_data *data, unsigned int room,
		unsigned int value);
int		lemin_find_node(t_lemin_data data, const char *name, unsigned int start);

int		lemin_valid_link(t_lemin_data *data, char *buff);

#endif
