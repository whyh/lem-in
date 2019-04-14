/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:33 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 20:32:05 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H

# define LEMIN_H

# include <sys/time.h>
# include "libft.h"
# include "lemin_structures.h"
# include "lemin_vis.h"
# include "lemin_errors.h"

# define LEMIN_CMND_START "##start"
# define LEMIN_CMND_END "##end"

# define LEMIN_NDONE 0
# define LEMIN_INPROGRESS 1
# define LEMIN_DONE 2

# define LEMIN_MIN_ANTS 1
# define LEMIN_MAX_ANTS (UI)INT_MAX
# define LEMIN_MAX_ROOMS (UI)INT_MAX
# define LEMIN_MAX_WAYS LEMIN_MAX_ROOMS
# define LEMIN_MAX_VALUE LEMIN_MAX_ROOMS
# define LEMIN_BAD_WAY LEMIN_MAX_WAYS + 1
# define LEMIN_INIT_VALUE LEMIN_MAX_VALUE + 1

int		lemin_parse(t_lemin_data *data, t_lemin_input *input);
int		lemin_parse_ants(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);
int		lemin_valid_room(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);
int		lemin_parse_rooms(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);
int		lemin_valid_link(t_lemin_data *data, char *buff);
int		lemin_parse_links(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);
int		lemin_find_node(t_lemin_data data, const char *name,
		unsigned int start);

int		lemin_set_way(t_lemin_data *data, unsigned int way_n);
int		lemin_set_value(t_lemin_data *data, unsigned int room,
		unsigned int value);
int		lemin_find_ways(t_lemin_data *data);

void	lemin_split_ants(t_lemin_data *data);
void	lemin_move_ants(t_lemin_data *data);
int		lemin_move_ants_turn(t_lemin_data *data, t_lemin_vis *vis);

void	lemin_exit(t_lemin_data *data, t_lemin_input *input, t_lemin_vis *vis);

#endif
