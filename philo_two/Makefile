# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sako <sako@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/17 22:22:39 by sako              #+#    #+#              #
#    Updated: 2020/06/17 07:37:21 by sako             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main_mac.c print.c set.c thread.c time.c util.c
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
