/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:33 by dderevyn          #+#    #+#             */
/*   Updated: 2019/03/15 13:26:26 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "../libft/libft.h"
# include "lemin_typedefs.h"

int		lemin_parse(t_lemin_data *data);
int		lemin_parse_ants(t_lemin_data *data, char *buff);
int		lemin_valid_rooms(t_lemin_data *data, char *buff);
int		lemin_valid_links(t_lemin_data *data, char *buff);
int		lemin_parse_rooms(t_lemin_data *data);
int		lemin_parse_links(t_lemin_data *data);
void	lemin_parse_skip_comment(t_lemin_data *data);
void	lemin_parse_compose(t_lemin_data *data, char **buff);

int		lemin_way(t_lemin_data *data, int w);
void	lemin_reset_w(t_lemin_data *data);

void	lemin_mark_graph(t_lemin_data *data, int n, int value);
int		lemin_find_node(t_lemin_data *data, const char *name, int start);

#endif
