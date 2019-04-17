/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_errors.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:55:15 by dderevyn          #+#    #+#             */
/*   Updated: 2019/04/14 21:15:13 by dderevyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_ERRORS_H

# define LEMIN_ERRORS_H

# define LEMIN_ERR "[redError: %s~]\n"
# define LEMIN_ERR_OPT "[redError: invalid option \"%s\"~]\n"
# define LEMIN_ERR_DIST "[redError: %s %d distance between all rooms~]"
# define LEMIN_ERR_DIST0 "option \"-v\" requires at least"

# define LEMIN_ERR_ANT0 "invalid symbol in the ant specification"
# define LEMIN_ERR_ANT1 "invalid number of ants"

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

# define LEMIN_ERR_LINK0 "invalid link specification"
# define LEMIN_ERR_LINK1 "link points to nonexistent room"
# define LEMIN_ERR_LINK2 "room is linked do itself"

# define LEMIN_ERR_BIG_GRAPH "the graph is way too big"

# define LEMIN_ERR_NO_WAYS "start and end of the farm are not connected"

# define LEMIN_ERR_VIS0 "SDL2 initialization failed"

# define LEMIN_USAGE "[greenUsage:~] ./lem-in\n[cyan%s%s%s%s~]\n"
# define LEMIN_USAGEV "[greenUsage:~] ./lem-in -v\n[cyan%s%s%s%s~]\n"
# define LEMIN_MAP0 "3\n"
# define LEMIN_MAP1 "##start\ns 50 500\n##end\ne 1450 500\n"
# define LEMIN_MAP2 "1 1000 200\n2 450 300\n3 900 400\n4 750 750\n"
# define LEMIN_MAP3 "s-1\n1-2\n4-2\n3-4\ns-3\ne-3"

#endif
