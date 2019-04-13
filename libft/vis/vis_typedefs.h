/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_typedefs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:52:21 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/13 19:08:44 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_TYPEDEFS_H
# define VIS_TYPEDEFS_H

# include "../libft.h"
# include "math.h"

# define R(RGB) (Uint8)(RGB >> 16)
# define G(RGB) (Uint8)((RGB << 8) >> 16)
# define B(RGB) (Uint8)(RGB)
# define RGB_MUSTARD_YELLOW 10066176
# define RGB_MAGMA_RED 9972992
# define RGB_BG_GREY 2105376
# define RGB_WHITE 16777215
# define RGB_GREY 6316128
# define RGB_BRIGHT_GREY 10526880
# define RGB_DARK_GREY 4210752
# define RGB_BG_VIOLET 3997849

typedef struct		s_vis_line
{
	SDL_Renderer	*rend;
	int 			x0;
	int 			y0;
	int 			x1;
	int 			y1;
	unsigned int	rgb0;
	unsigned int	rgb1;
	unsigned int	thikness;
	Uint8			opacity;
}					t_vis_line;

typedef struct		s_vis_process_line
{
	SDL_Renderer	*rend;
	double			x0;
	double			y0;
	double			x1;
	double			y1;
	unsigned int	rgb0;
	unsigned int	rgb1;
	unsigned int	thikness;
	Uint8			opacity;
	double			x;
	double			y;
	double			d;
	unsigned int	reversed : 1;
}					t_vis_process_line;

typedef struct		s_vis_rgba
{
	Uint8			r;
	Uint8			g;
	Uint8			b;
	Uint8			a;
}					t_vis_rgba;

#endif