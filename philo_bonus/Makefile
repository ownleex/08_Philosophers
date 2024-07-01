# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 22:37:59 by ayarmaya          #+#    #+#              #
#    Updated: 2024/07/01 02:13:06 by ayarmaya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus
PATH_SRC	=	src/
SRC			=	main_bonus.c \
				monitor_bonus.c \
				check_args_bonus.c \
				utils_bonus.c

SRCS		=	$(addprefix $(PATH_SRC), $(SRC))
OBJS		=	$(SRCS:.c=.o)
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS		=	-lpthread
HEADERS		=	-I./include
RM			= 	rm -f

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(HEADERS) $(LDFLAGS)

%.o: 		%.c
			$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
