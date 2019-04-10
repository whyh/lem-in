# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 20:30:28 by dderevyn          #+#    #+#              #
#    Updated: 2019/04/10 17:50:07 by dderevyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

OBJS_DIR = .$(patsubst %.a,%,$(NAME))_objects
CC = clang
CFLAGS = -Wall -Wextra -Werror
CLIBS = -F ./SDL -framework SDL2
RM = /bin/rm -rf
CP = cp -rf

LIBFT_PATH = libft/
LIBFT_INCS = libft.h
LIBFT = libft.a

LEM-IN_PATH = flemin/
LEM-IN_INCS = 		lemin.h\
					lemin_typedefs.h
LEM-IN_SRCS =		lemin.c\
					lemin_parse.c\
					lemin_parse_ants.c\
					lemin_parse_links.c\
					lemin_parse_valid_link.c\
					lemin_parse_rooms.c\
					lemin_parse_valid_room.c\
					lemin_mark_graph.c\
					lemin_utils.c\
					lemin_find_ways.c\
					lemin_move_ants.c\
					lemin_split_ants.c\
					lemin_vis.c\
					lemin_vis_keys.c\
					lemin_vis_render_bg.c\
					lemin_vis_mouse.c\
					lemin_vis_parse.c\
					lemin_vis_render_ants.c
LEM-IN_OBJS_DIR = $(OBJS_DIR)
LEM-IN_OBJS = $(LEM-IN_SRCS:%.c=$(LEM-IN_OBJS_DIR)/%.o)

SDL2_PATH = SDL/SDL2.framework/Headers/SDL.h
SDL2_INCS = SDL.h

SDL2GFX_PATH = SDL2_primitives/
SDL2GFX_INCS = 		SDL2_framerate.h\
					SDL2_gfxPrimitives.h\
					SDL2_gfxPrimitives_font.h\
					SDL2_imageFilter.h\
					SDL2_rotozoom.h
SDL2GFX_SRCS =		SDL2_framerate.c\
					SDL2_gfxPrimitives.c\
					SDL2_imageFilter.c\
					SDL2_rotozoom.c
SDL2GFX_OBJS_DIR = $(OBJS_DIR)
SDL2GFX_OBJS = $(SDL2GFX_SRCS:%.c=$(SDL2GFX_OBJS_DIR)/%.o)

all: libft $(NAME)

$(NAME): $(LEM-IN_OBJS) $(SDL2GFX_OBJS)
	@$(CC) $(CFLAGS) $(CLIBS) $^ -L $(LIBFT_PATH) -l$(patsubst %.a,%,$(LIBFT:lib%=%)) -o $(NAME)

$(LEM-IN_OBJS_DIR)/%.o: $(LEM-IN_PATH)%.c
	@mkdir -p $(LEM-IN_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(SDL2GFX_OBJS_DIR)/%.o: $(SDL2GFX_PATH)%.c
	@mkdir -p $(SDL2GFX_OBJS_DIR)
	@$(CC) -c $< -o $@

libft:
	@cd libft && make $(LIBFT)

clean:
	@cd libft && make clean
	@$(RM) $(OBJS_DIR)

fclean: clean
	@cd libft && make fclean
	@$(RM) $(NAME)

re: fclean all

norm:
	@cd libft && make norm
	@norminette $(addprefix $(LEM-IN_PATH),$(LEM-IN_SRCS)) \
	$(addprefix $(LEM-IN_PATH),$(LEM-IN_INCS))

test: rmt
	@mkdir -p test
	@$(CP) $(LIBFT_PATH) test/.
	@$(CP) author test/.
	@$(CP) Makefile test/.

rmt:
	@$(RM) test

.PHONY: all clean fclean re norm libft run test rmt