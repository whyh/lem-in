# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: danial <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 20:30:28 by dderevyn          #+#    #+#              #
#    Updated: 2019/06/18 15:42:02 by dderevyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		lem-in
INCS_PATH =	includes/
SRCS_PATH = srcs/
LIBS_PATH =	libs/
OBJS_DIR =	.objs/
UNAME_S =	$(shell uname -s)
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		/bin/rm -rf
CP =		cp -rf

LIBFT_PATH =		libft/
LIBFT_INCS_PATH =	$(LIBFT_PATH)$(INCS_PATH)
LIBFT =				libft.a

SDL2_PATH =			/Users/dderevyn/.brew/lib/
SDL2_INCS_PATH =	/Users/dderevyn/.brew/include/SDL2/
SDL2 =				libSDL2.dylib

SDL2_GFX_PATH =			/Users/dderevyn/.brew/lib/
SDL2_GFX_INCS_PATH =	/Users/dderevyn/.brew/include/SDL2/
SDL2_GFX =				libSDL2_gfx.dylib

SDL2_TTF_PATH =			/Users/dderevyn/.brew/lib/
SDL2_TTF_INCS_PATH =	/Users/dderevyn/.brew/include/SDL2/
SDL2_TTF =				libSDL2_ttf.dylib

CLIBS =	-L $(LIBFT_PATH) -l$(basename $(LIBFT:lib%=%)) \
		-L $(SDL2_PATH) -l$(basename $(SDL2:lib%=%)) \
		-L $(SDL2_GFX_PATH) -l$(basename $(SDL2_GFX:lib%=%)) \
		-L $(SDL2_TTF_PATH) -l$(basename $(SDL2_TTF:lib%=%)) 

LEMIN_INCS_PATH = 	$(INCS_PATH)
LEMIN_INCS =		lemin.h \
					lemin_errors.h \
					lemin_structures.h \
					lemin_vis.h \
					lemin_vis_structures.h
LEMIN_SRCS_PATH =	$(SRCS_PATH)
LEMIN_SRCS =		ft_aaline.c \
					ft_aaline_thin.c \
					lemin.c \
					lemin_exit.c \
					lemin_find_ways.c \
					lemin_mark_graph.c \
					lemin_move_ants.c \
					lemin_parse.c \
					lemin_parse_ants.c \
					lemin_parse_links.c \
					lemin_parse_rooms.c \
					lemin_parse_valid_link.c \
					lemin_parse_valid_room.c \
					lemin_split_ants.c \
					lemin_utils.c \
					lemin_vis.c \
					lemin_vis_keys.c \
					lemin_vis_mouse.c \
					lemin_vis_parse.c \
					lemin_vis_render_ants.c \
					lemin_vis_render_bg.c \
					lemin_vis_render_text.c \
					vis_line_gradient.c
LEMIN_OBJS_DIR =	$(OBJS_DIR)
LEMIN_OBJS =		$(LEMIN_SRCS:%.c=$(LEMIN_OBJS_DIR)%.o)

all: $(LIBFT_PATH)$(LIBFT) $(NAME)

$(LIBFT_PATH)$(LIBFT):
	@make -s $(LIBFT) -C $(LIBFT_PATH)

$(NAME): $(LEMIN_OBJS)
	@$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

$(LEMIN_OBJS_DIR)%.o: $(SRCS_PATH)%.c
	@mkdir -p $(LEMIN_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ \
	-I$(LEMIN_INCS_PATH) \
	-I$(LIBFT_INCS_PATH) \
	-I$(SDL2_INCS_PATH) \
	-I$(SDL2_GFX_INCS_PATH) \
	-I$(SDL2_TTF_INCS_PATH)

clean:
	@make -s clean -C $(LIBFT_PATH)
	@$(RM) $(OBJS_DIR)

fclean: clean
	@make -s fclean -C $(LIBFT_PATH)
	@$(RM) $(NAME)

re: fclean all

norm:
	@make -s norm -C $(LIBFT_PATH)
	@norminette \
	$(addprefix $(SRCS_PATH),$(LEMIN_SRCS)) \
	$(addprefix $(INCS_PATH),$(LEMIN_INCS))

.PHONY: all clean fclean re norm
