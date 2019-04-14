/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:49:13 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 23:02:08 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_VIS_H

# define LEMIN_VIS_H

# include "SDL.h"
# include "SDL2_gfxPrimitives.h"
# include "SDL_ttf.h"
# include "lemin_vis_structures.h"

# define R(RGB) (Uint8)(RGB >> 16)
# define G(RGB) (Uint8)((RGB << 8) >> 16)
# define B(RGB) (Uint8)(RGB)

# define RGB_MUSTARD_YELLOW 10066176
# define RGB_MAGMA_RED 9972992
# define RGB_BG_GREY 2105376
# define RGB_WHITE 16777215
# define RGB_GREY 6316128
# define RGB_BRIGHT_GREY 6515312
# define RGB_DARK_GREY 4210752
# define RGB_ASPHALT_GREY 4474186
# define RGB_NIGHT_BLUE 662568
# define RGB_BLUE 48569

# define LEMIN_RGB_BG RGB_NIGHT_BLUE
# define LEMIN_RGB_ANT RGB_ASPHALT_GREY
# define LEMIN_RGB_LINK RGB_BRIGHT_GREY
# define LEMIN_RGB_BORDER RGB_BLUE
# define LEMIN_RGB_COUNTER RGB_GREY

# define LEMIN_VIS_WIN_NAME "lem-in"
# define LEMIN_VIS_WIN_W 1500
# define LEMIN_VIS_WIN_H 1000

# define LEMIN_VIS_BRAD_MIN 25
# define LEMIN_VIS_SRAD_MIN 10
# define LEMIN_VIS_WAY_LEN_MIN 1

# define LEMIN_VIS_TMP LEMIN_VIS_BRAD_MIN * 2 + LEMIN_VIS_START_ZOOM * 2
# define LEMIN_VIS_MIN_DIST LEMIN_VIS_TMP + LEMIN_VIS_WAY_LEN_MIN

# define LEMIN_COUNTER_TEXT "TURN: "
# define LEMIN_COUNTER_W 100
# define LEMIN_COUNTER_H 30
# define LEMIN_COUNTER_X LEMIN_VIS_WIN_W - LEMIN_COUNTER_W - 50
# define LEMIN_COUNTER_Y 5
# define LEMIN_VIS_ZOOMF 1
# define LEMIN_VIS_START_ZOOM 0
# define LEMIN_S_BTW_TURNS 2



int		lemin_vis(t_lemin_data *data, t_lemin_vis *vis);

int		lemin_vis_parse(t_lemin_data *data, t_lemin_vis *vis, int argc,
		char **argv);

void	lemin_vis_render_bg(t_lemin_data *data, t_lemin_vis *vis);
int		lemin_vis_render_ants(t_lemin_data *data, t_lemin_vis *vis,
		unsigned int move);
void	lemin_vis_render_text(t_lemin_vis *vis);

void	lemin_vis_keydown(t_lemin_vis *vis);
void	lemin_vis_keyup(t_lemin_vis *vis);

void	lemin_vis_mouse_motion(t_lemin_vis *vis);
void	lemin_vis_mouse_buttondown(t_lemin_vis *vis);
void	lemin_vis_mouse_buttonup(t_lemin_vis *vis);
void	lemin_vis_mouse_wheel(t_lemin_vis *vis);

void	ft_aaline(t_vis_line *line);
void	ft_aaline_thin(t_vis_line *line);
void	ft_line_gradient(t_vis_process_line *pl, SDL_Color *color);

#endif
