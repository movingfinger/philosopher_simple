/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/06/13 12:00:54 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int food_on_table (t_philosophers *philo)
{
	if (food_limit == -1)
	{
		philo->state = 6;
		printf("%lld ms - Philosopher %d food left infinite\n", timestamp[philo->pos], philo->pos);
		philo->eat_count++;
	}
	else
	{
		philo->state = 7;
		printf("%lld ms - Philosopher %d food left %d\n", timestamp[philo->pos], philo->pos, philo->eat_count);
		philo->eat_count--;
	}
	*philo->sem_val -= 2;	
	return (philo->eat_count);
}

void	philosopher (t_philosophers *philo, int *death)
{
	int i;
	pthread_t thread;

	i = 0;
	pthread_create(&philo->thread_philo_time, NULL, philo_life, philo);
	pthread_create(&thread, NULL, timer, &time_basic);
	while (*philo->death > 0)
	{
		philo->state = 1;
		printf("%lld ms - Philosoher %d is thinking\n", timestamp[philo->pos], philo->pos);
		eat(philo);
		if (food_limit > 0)
		{
			i++;
			if (i >= food_limit)
			{
				printf("PHIL %d exited\n",philo->pos);
				*death -= 1;
				printf("Death %d exited\n",*death);
				exit(0);
			}
		}
		philo->state = 2;
		printf("%lld ms - Philosopher %d is sleeping\n", timestamp[philo->pos], philo->pos);
		usleep(sleep_seconds * 1000);
	}
	*philo->death = -1;
	exit (0);
}

void Spawn(int *sem_c, int *death)
{
	t_philosophers *philo;
	static int i;

	philo = (t_philosophers *)malloc(sizeof(t_philosophers));
	philo->pos = i;
	if (food_limit == -1)
		philo->eat_count = 0;
	else
		philo->eat_count = food_limit;
	philo->state = 1;
	philo->death = death;
	philo->time = 0;
	philo->sem_val = sem_c;
	if (fork() == 0)
		philosopher(philo, death);	
}

void eat(t_philosophers *philo)
{
	pthread_t thread;
	sem_t *sem;
	int id;

	sem = sem_open("SEM_3", O_RDWR);
	id = philo->pos;
	while (!food_on_table(philo));
	printf ("%lld ms - Philosopher %d has taken a fork\n", timestamp[id], id);
	sem_wait(sem);
	printf ("%lld ms - Philosopher %d has taken a fork\n", timestamp[id], id);
	sem_wait(sem);
	philo->state = 0;
	usleep(eat_seconds * 1000);
	pthread_create(&thread, NULL, philo_life, philo);
	sem_post(sem);
	sem_post(sem);
	sem_close(sem);
	*philo->sem_val += 2;
	printf ("%lld ms - Philosopher %d eating\n", timestamp[id], id);
}