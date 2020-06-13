/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:49 by sako              #+#    #+#             */
/*   Updated: 2020/06/13 12:00:38 by sako             ###   ########.fr       */
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
#include <sys/time.h>
#include <sys/stat.h>
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
long long		num_can_eat;				// num_philo - 1 for token system
long long		sleep_seconds;			// time to sleep
long long		eat_seconds;				// time to eat
long long		die_seconds;				// time to die
long long		food_limit;				// number of times each philosopher must eat. If -1, it means not defined.
long long		*timestamp;
long			time_basic;
int				check_food;
int				sem_val;

typedef struct	s_philosophers
{
	int			pos;
	int			eat_count;
	int			state;
	long		*time;
	int			*death;
	int			len;
	char		*print_str;
	int			*sem_val;
	pthread_t	thread_philo;
	pthread_t	thread_philo_time;
}				t_philosophers;

void			philosopher (t_philosophers *philo, int *death);
void			grab_fork (t_philosophers *philo, int fork, int side);
void			down_forks (int, int);

int				food_on_table (t_philosophers *philo);
void			get_token ();
void			return_token ();
void			eat(t_philosophers *philo);
void			Spawn(int *sem_c, int *death);

void			*philo_life(void *arg);
void			*timer(void *var);

void			ft_print_error(const char *str);
long long		ft_atol (const char *str);
size_t			ft_strlen(const char *str);
size_t			ft_strlcat (char *dst, const char *src, size_t dstsize);
unsigned int	ft_nbrlen(long long nbr, int base);
char			*ft_strnew(size_t size);
char			*ft_ltoa_base(long long nbr, int base);
void			set_param(char **av, int ac);

#endif