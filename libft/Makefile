# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dderevyn <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/21 20:30:28 by dderevyn          #+#    #+#              #
#    Updated: 2019/04/14 17:48:15 by dderevyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a
OBJS_DIR =	.objs/
SRCS_PATH =	srcs/
INCS_PATH =	includes/
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		/bin/rm -rf

LIBFT_INCS_PATH =	$(INCS_PATH)
LIBFT_INCS =		libft.h\
					libft_typedefs.h
LIBFT_SRCS_PATH =	$(SRCS_PATH)
LIBFT_SRCS = 		ft_abs.c\
					ft_atoibase.c\
					ft_itoabase.c\
					ft_memalloc.c\
					ft_memcmp.c\
					ft_memdel.c\
					ft_memmove.c\
					ft_memset.c\
					ft_nbr_len.c\
					ft_strchr.c\
					ft_strdel.c\
					ft_strfrepl.c\
					ft_strin.c\
					ft_strjoin.c\
					ft_strlen.c\
					ft_strncmp.c\
					ft_strncpy.c\
					ft_strndup.c\
					ft_strneject.c\
					ft_strnew.c\
					ft_strnin.c\
					ft_strninject.c\
					ft_strrchr.c\
					ft_swap.c
LIBFT_OBJS_DIR =	$(OBJS_DIR)$(basename $(NAME))/
LIBFT_OBJS =		$(LIBFT_SRCS:%.c=$(LIBFT_OBJS_DIR)%.o)

GNL_PATH = 		ft_gnl/
GNL_INCS_PATH =	$(GNL_PATH)$(INCS_PATH)
GNL_INCS =		ft_gnl_typedefs.h
GNL_SRCS_PATH =	$(GNL_PATH)$(SRCS_PATH)
GNL_SRCS =		ft_gnl.c
GNL_OBJS_DIR =	$(OBJS_DIR)$(GNL_PATH)
GNL_OBJS =		$(GNL_SRCS:%.c=$(GNL_OBJS_DIR)%.o)

PRINTF_PATH =		ft_printf/
PRINTF_INCS_PATH =	$(PRINTF_PATH)$(INCS_PATH)
PRINTF_INCS =		ft_printf.h\
					ft_printf_typedefs.h
PRINTF_SRCS_PATH =	$(PRINTF_PATH)$(SRCS_PATH)
PRINTF_SRCS =		ft_printf.c\
					ft_printf_cspf.c\
					ft_printf_diouxx.c\
					ft_printf_fill_funs.c\
					ft_printf_hash_zero_blank_plus.c\
					ft_printf_parse.c\
					ft_printf_prec.c\
					ft_printf_width.c\
					ft_printf_mod0_b_cap_udo.c\
					ft_printf_0_base.c\
					ft_printf_lhllhhl.c\
					ft_printf_zjt.c\
					ft_printf_r.c\
					ft_printf_unicode.c\
					ft_printf_parce_funs.c\
					ft_printf_color.c
PRINTF_OBJS_DIR =	$(OBJS_DIR)$(PRINTF_PATH)
PRINTF_OBJS =		$(PRINTF_SRCS:%.c=$(PRINTF_OBJS_DIR)%.o)

all: $(NAME)

$(NAME): $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	@ar rc $(NAME) $^
	@ranlib $(NAME)

$(LIBFT_OBJS_DIR)%.o: $(LIBFT_SRCS_PATH)%.c
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(LIBFT_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -I$(INCS_PATH) -o $@

$(GNL_OBJS_DIR)%.o: $(GNL_SRCS_PATH)%.c
	@mkdir -p $(GNL_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -I$(INCS_PATH) -I$(GNL_INCS_PATH) -o $@

$(PRINTF_OBJS_DIR)%.o: $(PRINTF_SRCS_PATH)%.c
	@mkdir -p $(PRINTF_OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -I$(INCS_PATH) -I$(PRINTF_INCS_PATH) -o $@

clean:
	@$(RM) $(OBJS_DIR)

fclean: clean
	@$(RM) $(NAME)make

re: fclean all

norm:
	@norminette \
	$(addprefix $(INCS_PATH),$(LIBFT_INCS)) \
	$(addprefix $(SRCS_PATH),$(LIBFT_SRCS)) \
	$(addprefix $(GNL_SRCS_PATH),$(GNL_SRCS)) \
	$(addprefix $(GNL_INCS_PATH),$(GNL_INCS)) \
	$(addprefix $(PRINTF_SRCS_PATH),$(PRINTF_SRCS)) \
	$(addprefix $(PRINTF_INCS_PATH),$(PRINTF_INCS))

.PHONY: all clean fclean re norm
