# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sako <sako@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 21:58:49 by sako              #+#    #+#              #
#    Updated: 2020/06/26 10:10:03 by sako             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c print.c setup.c thread.c diner.c util.c
OBJS		= $(SRCS:.c=.o)

GCC			= gcc
RM			= rm -f
CFLAGS		= -Wextra -Werror -Wall -I.
LIBS		= -lpthread

NAME		= philo_two

all:		$(NAME)

$(NAME):	$(OBJS)
			gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean $(NAME)

.PHONY:		all clean fclean re
