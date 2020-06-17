/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 08:02:34 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int food_on_table (t_philosophers *philo)
{
	printf("%lld timestamp\n", timestamp[0]);
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
	
	return (philo->eat_count);
}

void *philosopher (void *arg)
{
	t_philosophers *philo;
	int i;

	philo = arg;
	i = 0;
	pthread_create(&philo->thread_philo_time, NULL, philo_life, philo);
	while ((i = food_on_table(philo)))
	{
		philo->state = 1;
		printf("%lld ms - Philosoher %d is thinking\n", timestamp[philo->pos], philo->pos);
		eat(philo);
		philo->state = 2;
		printf("%lld ms - Philosopher %d is sleeping\n", timestamp[philo->pos], philo->pos);
		usleep(sleep_seconds * 1000);
	}

	if (!i)
	{
		philo->state = 4;
		printf("%lld ms - Philosopher %d died due to lack of food\n", timestamp[philo->pos], philo->pos);
		exit (0);
	}
	if (food_limit == 0)
		ft_print_error("No food left!");

	pthread_exit(0);
	return (NULL);
}

void Spawn(t_philosophers *philo, sem_t *sem, long *time, int i)
{
	static int death;

	philo->pos = i;
	if (food_limit == -1)
		philo->eat_count = 0;
	else
		philo->eat_count = food_limit;
	philo->state = 1;
	philo->death = &death;
	philo->time = time;
	philo->sem = sem;
	sem_val = num_philo;

	pthread_create(&philo->thread_philo, NULL, philosopher, philo);
}

void eat(t_philosophers *philo)
{
	int id;

	id = philo->pos;
	printf("%lld ms - Philosopher %d has taken a fork\n", timestamp[id], id);
	sem_wait(philo->sem);
	printf("%lld ms - Philosopher %d has taken a fork\n", timestamp[id], id);
	sem_wait(philo->sem);
	philo->state = 0;
	usleep(eat_seconds * 1000);
	pthread_create(&philo->thread_philo_time, NULL, philo_life, philo);
	sem_post(philo->sem);
	sem_post(philo->sem);
	sem_close(philo->sem);
	printf("%lld ms - Philosopher %d eating\n", timestamp[id], id);
}
