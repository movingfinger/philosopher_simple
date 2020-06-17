/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:49 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 12:17:58 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
//#include <sys/stat.h>
#include <fcntl.h>

//#define DELAY 5000
#define ERR_NEG "Negative numbers are not allowed! You need to type positive numbers only!\n"
#define ERR_NONUM "You must type nubmers only!\n"
#define ERR_ARG "Argument should be 5 or 6\n"\
"1. Number of Philosophers\n"\
"2. Time to die\n"\
"3. Time to eat\n"\
"5. Time to sleep\n"\
"4. Eat count for each philosophers [Optional]"
#define ERR_NUMMAX "Philosophers should not be over 100!"
#define ERR_INTMAX "Argument 2 ~ 6 should not be over int max!"
# define L_FORK "left"
# define R_FORK "right"

long long		num_philo;				// number of philosophers
long long		num_can_eat;			// num_philo - 1 for token system
long long		sleep_seconds;			// time to sleep
long long		eat_seconds;			// time to eat
long long		die_seconds;			// time to die
long long		food_limit;				// number of times each philosopher must eat. If -1, it means not defined.
long long		start_time;
int				check_food;
int				sem_val;
sem_t			*sem_fork;
sem_t			*sem_print;
sem_t			*sem_dead;
sem_t			*sem_dead_report;

/*
** state 0: eating
** state 1: thinking
** state 2: sleeping
** state 3: died timeover
** state 4: died no food
** state 5: grab fork
** state 6: infinite food
** state 7: check food left
** state 8: food limit reached
*/

typedef struct	s_philosophers
{
	int			pos;
	int			eat_count;
	int			state;
	long long	last_time;
	long long	limit;
	long long	*time;
	int			*death;
	int			lfork;
	int			rfork;
	pid_t		pid;
	sem_t		*sem;
	sem_t		*food_limit;
}				t_philosophers;

void			grab_fork (t_philosophers *philo, int fork, int side);
void			down_forks (int, int);

void			eat(t_philosophers *philo);
void			Spawn(t_philosophers *philo);

long long		timer(void);

void			ft_print_error(const char *str);
long long		ft_atol (const char *str);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat (char *dst, const char *src, size_t dstsize);
unsigned int	ft_nbrlen(long long nbr, int base);
char			*ft_strnew(size_t size);
char			*ft_ltoa_base(long long nbr, int base);
void			set_param(char **av, int ac);

void			print_message(t_philosophers *philo, int num);

void			grab_forks(t_philosophers *philo);
void			drop_forks(t_philosophers *philo);

char			*make_semaphore(const char *str, int i);
#endif