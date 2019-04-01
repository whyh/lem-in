# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 20:30:28 by dderevyn          #+#    #+#              #
#    Updated: 2019/03/12 19:53:32 by dderevyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

OBJS_DIR = .$(patsubst %.a,%,$(NAME))_objects
CC = clang
CFLAGS = -Wall -Wextra -Werror
CLIBS = -lmlx -framework OpenGL -framework AppKit
RM = /bin/rm -rf
CP = cp -rf

LIBFT_PATH = libft/
LIBFT = libft.a

LEM-IN_PATH = flemin/
LEM-IN_INCS = 		lemin.h\
					lemin_typedefs.h
LEM-IN_SRCS =		lemin.c\
					lemin_parse.c\
					lemin_parse_ants.c\
					lemin_parse_links.c\
					lemin_parse_rooms.c\
					lemin_mark_graph.c\
					lemin_utils.c\
					lemin_find_ways.c\
					lemin_move_ants.c\
					lemin_split_ants.c
LEM-IN_OBJS_DIR = $(OBJS_DIR)
LEM-IN_OBJS = $(LEM-IN_SRCS:%.c=$(LEM-IN_OBJS_DIR)/%.o)

all: libft $(NAME)

$(NAME): $(LEM-IN_OBJS)
	@$(CC) $(CFLAGS) $^ -L $(LIBFT_PATH) -l$(patsubst %.a,%,$(LIBFT:lib%=%)) -o $(NAME)

$(LEM-IN_OBJS_DIR)/%.o: $(LEM-IN_PATH)%.c
	@mkdir -p $(LEM-IN_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< $(addprefix -I.,$(addprefix $(LEM-IN_PATH),$(LEM-IN_INCS))) -o $@

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
	@$(CP) $(PUSH_SWAP_PATH) test/.
	@$(CP) mlx test/.
	@$(CP) author test/.
	@$(CP) Makefile test/.

rmt:
	@$(RM) test

.PHONY: all clean fclean re norm libft run test rmt