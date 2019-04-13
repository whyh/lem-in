/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:51:35 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/10 18:56:43 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIS_H
# define VIS_H

# include "../libft.h"
# include <SDL2/SDL.h>
# include "vis_typedefs.h"

void	ft_aaline(t_vis_line *line);
void	ft_aaline_thin(t_vis_line *line);
void	ft_line_gradient(t_vis_process_line *pl, t_vis_rgba *color);

#endif
