/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_vis_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:48:23 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 20:56:51 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_VIS_STRUCTURES_H
# define LEMIN_VIS_STRUCTURES_H

typedef struct			s_vis_line
{
	SDL_Renderer		*rend;
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	unsigned int		rgb0;
	unsigned int		rgb1;
	unsigned int		thikness;
	Uint8				opacity;
}						t_vis_line;

typedef struct			s_vis_process_line
{
	SDL_Renderer		*rend;
	double				x0;
	double				y0;
	double				x1;
	double				y1;
	unsigned int		rgb0;
	unsigned int		rgb1;
	unsigned int		thikness;
	Uint8				opacity;
	double				x;
	double				y;
	double				d;
	unsigned int		reversed : 1;
}						t_vis_process_line;

typedef struct			s_lemin_vis_keys
{
	unsigned int		esc : 1;
	unsigned int		c : 1;
	unsigned int		space : 1;
	unsigned int		left : 1;
}						t_lemin_vis_keys;

typedef struct			s_lemin_vis_text
{
	TTF_Font			*font;
	SDL_Color			color;
	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDL_Rect			box;
}						t_lemin_vis_text;

typedef struct			s_lemin_vis
{
	unsigned int		vis : 1;
	unsigned int		pause : 1;
	unsigned int		moved : 1;
	unsigned int		zoom;
	unsigned int		prev_zoom;
	int					pos_x;
	int					pos_y;
	unsigned int		*links0;
	unsigned int		*links1;
	unsigned int		min_dist;
	double				*ant_posx;
	double				*ant_posy;
	char				*delta;
	double				*delta2;
	unsigned int		turns;
	unsigned int		counter;
	t_lemin_vis_keys	keyup;
	SDL_Event			event;
	SDL_Window			*win;
	SDL_Renderer		*rend;
}						t_lemin_vis;

#endif
