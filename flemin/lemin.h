/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:33 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/09 16:19:33 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H

# define LEMIN_H

# include "../../../includes/SDL2/SDL.h"
# include "../SDL2_primitives/SDL2_gfxPrimitives.h"
# include "../libft/libft.h"
# include "lemin_typedefs.h"

int		lemin_parse(t_lemin_data *data, t_lemin_input *input);
int		lemin_parse_ants(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);
int		lemin_parse_rooms(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);
int		lemin_parse_links(t_lemin_data *data, t_lemin_parse *parse,
		t_lemin_input *input);

int		lemin_find_way(t_lemin_data *data);
void	lemin_split_ants(t_lemin_data *data);

int		lemin_valid_room(t_lemin_data *data, t_lemin_parse *parse,
		const char *buff);

int		lemin_set_way(t_lemin_data *data, unsigned int way_n);
int		lemin_set_value(t_lemin_data *data, unsigned int room,
		unsigned int value);
int		lemin_find_node(t_lemin_data data, const char *name,
		unsigned int start);

int		lemin_valid_link(t_lemin_data *data, char *buff);

int		lemin_vis_parse(t_lemin_data *data, t_lemin_vis *vis, int argc, char **argv);
int		lemin_vis(t_lemin_data *data, t_lemin_vis *vis);

void	lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis);

void	lemin_vis_keydown(t_lemin_vis *vis);
void	lemin_vis_keyup(t_lemin_vis *vis);

void	lemin_vis_mouse_motion(t_lemin_vis *vis);
void	lemin_vis_mouse_buttondown(t_lemin_vis *vis);
void	lemin_vis_mouse_buttonup(t_lemin_vis *vis);
void	lemin_vis_mouse_wheel(t_lemin_vis *vis);

unsigned int	lemin_move_ants_turn(t_lemin_data *data, t_lemin_vis *vis);

void	lemin_move_ants(t_lemin_data *data, t_lemin_vis *vis);

void	lemin_vis_render_ants(t_lemin_data *data, t_lemin_vis *vis);
void	lemin_vis_handle_events(t_lemin_vis *vis);

#endif
