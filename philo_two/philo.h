/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:49 by sako              #+#    #+#             */
/*   Updated: 2020/06/27 22:58:15 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <assert.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>

# define ERR_NEG	"Negative numbers are not allowed! "\
					"You need to type positive numbers only!\n"
# define ERR_NONUM	"You must type nubmers only!\n"
# define ERR_ARG	"Argument should be 5 or 6\n"\
					"1. Number of Philosophers\n"\
					"2. Time to die\n"\
					"3. Time to eat\n"\
					"5. Time to sleep\n"\
					"4. Eat count for each philosophers [Optional]"
# define ERR_NUMMAX	"Philosophers should be between 0 to 200!"
# define ERR_INTMAX	"Argument 2 ~ 6 should not be over int max!"
# define L_FORK		"left"
# define R_FORK		"right"

# define ST_EAT		0
# define ST_SLEEP	1
# define ST_THINK	2
# define ST_FORK	3
# define ST_DIE		4
# define ST_DONE	5

struct s_status;

typedef struct		s_philosophers
{
	int				id;
	int				is_eating;
	long long		check_time;
	long long		eat_time;
	int				eat_count;
	int				l_fork;
	int				r_fork;
	struct s_status	*status;
	sem_t			*sem_mutex;
	sem_t			*sem_eat;
}					t_philosophers;

//	check_time is check whether philosopher failed to eat food in time or not.

typedef struct		s_status
{
	int				num_philo;
	int				num_can_eat;
	long long		must_eat;
	long long		start_time;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	t_philosophers	*philo;
	sem_t			*sem_message;
	sem_t			*sem_dead;
	sem_t			*sem_fork;
	sem_t			*num_can_eat_lock;
}					t_status;

void				*check_count(void *temp_status);
//void				*check_philosopher(void *t_philo);
//void				*philosopher (void *t_philo);
void				do_philosopher(t_status *status);
void				free_status(t_status *status);

void				get_token (t_philosophers *philo);
void				return_token(t_philosophers *philo);
void				eat(t_philosophers *philo);
void				grab_fork (t_philosophers *philo);
void				down_forks (t_philosophers *philo);

void				error_check(char **av);
void				init_semaphore(t_status *status);
int					init_philo(t_status *status);
void				set_param(int ac, char **av, t_status *status);
sem_t				*ft_sem_open(const char *str, int num);

void				ft_print_error(const char *str);
void				print_input(t_status *status);
int					print_status(t_philosophers *philo, int stat);
char				*make_semaphore(const char *str, int i);

long long			ft_atol (const char *str);
size_t				ft_strlen(const char *str);
size_t				ft_strlcat (char *dst, const char *src, size_t dstsize);
unsigned int		ft_nbrlen(long long num, int base);
char				*ft_strnew(size_t size);
char				*ft_ltoa_base(long long nbr, int base);
long long			timer(void);

#endif