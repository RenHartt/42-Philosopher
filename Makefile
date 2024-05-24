# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 14:46:56 by bgoron            #+#    #+#              #
#    Updated: 2024/04/16 15:19:01 by bgoron           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror

IFLAGS = -I ./include

SRCS =             \
src/loop.c         \
src/philosophers.c \
src/routine.c      \
src/setup.c        \
src/utils.c        \

OBJS_DIR := .objs

OBJS := $(addprefix $(OBJS_DIR)/, $(SRCS:%.c=%.o))

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@

clean :
	@rm -rf $(OBJS)

dclean : clean
	@rm -rf $(OBJS_DIR)

fclean : dclean
	@rm -rf $(NAME)

re : fclean all

all: $(NAME)

.PHONY: all clean fclean re