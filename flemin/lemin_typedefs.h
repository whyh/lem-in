/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_typedefs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:15:07 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/08 19:26:48 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_TYPEDEFS_H

# define LEMIN_TYPEDEFS_H

# define LEMIN_CMND_START "##start"
# define LEMIN_CMND_END "##end"
# define LEMIN_NDONE 0
# define LEMIN_INPROGRESS 1
# define LEMIN_DONE 2
# define LEMIN_MIN_ANTS 1
# define LEMIN_MAX_ANTS INT_MAX
# define LEMIN_MAX_ROOMS 10000 //TODO change to intmax
# define LEMIN_MAX_WAYS LEMIN_MAX_ROOMS
# define LEMIN_MAX_VALUE LEMIN_MAX_ROOMS
# define LEMIN_BAD_WAY LEMIN_MAX_WAYS + 1
# define LEMIN_INIT_VALUE LEMIN_MAX_VALUE + 1
# define LEMIN_WIN_W 1500
# define LEMIN_WIN_H 1000
# define LEMIN_VIS_BRAD_MIN 25
# define LEMIN_VIS_SRAD_MIN 10
# define LEMIN_VIS_WAY_LEN_MIN 1
# define LEMIN_VIS_ZOOMF 1
# define LEMIN_VIS_START_ZOOM 0
# define LEMIN_VIS_MIN_DIST LEMIN_VIS_BRAD_MIN * 2 + LEMIN_VIS_START_ZOOM * 2\
+ LEMIN_VIS_WAY_LEN_MIN
# define LEMIN_VIS_WIN_NAME "lem-in"
# define LEMIN_ERR_NO_WAYS "start and end of the farm are not connected"

# define LEMIN_ERR_BIG_GRAPH "graph is way too big"

# define LEMIN_USAGE "[greenUsage:~] ./lem-in\n[cyan%s~]\n"

# define LEMIN_USAGE_MAP0 "map"//TODO add map sample

# define LEMIN_ERR "[redError: %s\n"

# define LEMIN_ERR_OPT "[redError: invalid option \"%s\"\n"

# define LEMIN_ERR_DIST "[redError: %s %d~]"

# define LEMIN_ERR_VIS0 "visualisation error"
# define LEMIN_ERR_VIS3 "with -v option required min distance between the rooms "//TODO change

# define LEMIN_ERR_ANT0 "invalid symbol in the ant specification"
# define LEMIN_ERR_ANT1 "invalid number of ants"

# define LEMIN_ERR_LINK0 "invalid link specification"
# define LEMIN_ERR_LINK1 "link points to nonexistent room"
# define LEMIN_ERR_LINK2 "room is linked do itself"

# define LEMIN_ERR_START0 "start points on the same room as end"
# define LEMIN_ERR_START1 "\"##start\" command before ant specification"
# define LEMIN_ERR_START2 "start was not specified before the links"
# define LEMIN_ERR_START3 "start specified twice"

# define LEMIN_ERR_END0 "end points on the same room as start"
# define LEMIN_ERR_END1 "\"##end\" command before ant specification"
# define LEMIN_ERR_END2 "end was not specified before the links"
# define LEMIN_ERR_END3 "end specified twice"

# define LEMIN_ERR_ROOM0 "invalid symbol in the room specification"
# define LEMIN_ERR_ROOM1 "invalid room specification"
# define LEMIN_ERR_ROOM2 "parameter in the room specification is duplicated"
# define LEMIN_ERR_ROOM3 "at least one coordinate is too big or too small"

typedef struct				s_lemin_vis_keys
{
	unsigned int			esc : 1;
	unsigned int			h : 1;
	unsigned int			space : 1;
	unsigned int			left : 1;
}							t_lemin_vis_keys;

typedef struct				s_lemin_vis
{
	unsigned int			vis : 1;
	unsigned int			pause : 1;
	unsigned int			zoom;
	unsigned int			prev_zoom;
	int 					pos_x;
	int 					pos_y;
	unsigned int			*links0;
	unsigned int			*links1;
	unsigned int			min_dist;
	int						prev_posx;
	int						prev_posy;
	int 					*ant_posx;
	int 					*ant_posy;
	unsigned int 			*deltax;
	unsigned int 			*deltay;
	t_lemin_vis_keys		keyup;
	SDL_Event				event;
	SDL_Window				*win;
	SDL_Renderer			*rend;
}							t_lemin_vis;

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

typedef struct				s_lemin_node
{
	char					*name;
	int						x;
	int						y;
	int 					rad;
	int						ant;
	unsigned int			n;
	unsigned int			value;
	unsigned int			w;
	unsigned int			n_links;
	struct s_lemin_node		**links;
}							t_lemin_node;

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
	t_lemin_node			*graph;
	t_lemin_way				*ways;
	t_lemin_ant				*ants;
	unsigned int			n_ways;
	unsigned int			n_nodes;
	unsigned int			n_links;
	unsigned int			end;
	unsigned int			start;
	unsigned int			n_ants;
}							t_lemin_data;

#endif
