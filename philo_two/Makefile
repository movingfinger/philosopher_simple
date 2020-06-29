# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sako <sako@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
<<<<<<< HEAD
#    Created: 2020/06/17 21:58:49 by sako              #+#    #+#              #
#    Updated: 2020/06/26 10:10:03 by sako             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c print.c setup.c thread.c diner.c util.c
=======
#    Created: 2020/06/17 22:22:39 by sako              #+#    #+#              #
#    Updated: 2020/06/17 07:37:21 by sako             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main_mac.c print.c set.c thread.c time.c util.c
>>>>>>> 8b0f2ab3287f884a1b03e5ae11ddd275de945a73
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
