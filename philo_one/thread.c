/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/06/11 12:52:16 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int food_on_table (t_philosophers *philo)
{
	pthread_mutex_lock (&food_lock);
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
	
	pthread_mutex_unlock (&food_lock);
	return (philo->eat_count);
}

void *philosopher (void *arg)
{
	t_philosophers *philo;
	int i;
	int left_fork;
	int right_fork;

	philo = arg;
	right_fork = philo->pos;
	left_fork = philo->pos + 1;
	i = 0;

	if (left_fork == num_philo)
		left_fork = 0;
	pthread_create(&philo->thread_philo_time, NULL, philo_life, philo);
	while ((i = food_on_table(philo)))
	{
		philo->state = 1;
		printf("%lld ms - Philosoher %d is thinking\n", timestamp[philo->pos], philo->pos);
		eat(philo, left_fork, right_fork);
		pthread_create(&philo->thread_philo_time, NULL, philo_life, philo);
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

void Spawn(t_philosophers *philo, long *time, int i)
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

	pthread_create(&philo->thread_philo, NULL, philosopher, philo);
}

void eat(t_philosophers *philo, int left, int right)
{
	int id;

	id = philo->pos;
	get_token ();

	grab_fork(philo, right, 0);
	grab_fork(philo, left, 1);

	philo->state = 0;
	printf("%lld ms - Philosopher %d: eating\n", timestamp[id], id);
	usleep(eat_seconds * 1000);
	down_forks (left, right);
	return_token ();
}

void grab_fork (t_philosophers *philo, int fork, int side)
{
	int id;

	id = philo->pos;
	pthread_mutex_lock (&m_fork[fork]);
	philo->state = 5;
	if (side == 0)
		printf ("%lld ms - Philosopher %d: has taken %s fork %d\n", timestamp[id], id, "L", fork);
	else
		printf ("%lld ms - Philosopher %d: has taken %s fork %d\n", timestamp[id], id, "R", fork);
}

void down_forks (int c1, int c2)
{
	pthread_mutex_unlock (&m_fork[c1]);
	pthread_mutex_unlock (&m_fork[c2]);
}

void get_token ()
{
	int successful;

	successful = 0;
	while (!successful)
	{
		pthread_mutex_lock (&num_can_eat_lock);
		if (num_can_eat > 0)
		{
			num_can_eat--;
			successful = 1;
		}
		else
			successful = 0;
		pthread_mutex_unlock (&num_can_eat_lock);
	}
}

void return_token ()
{
	pthread_mutex_lock (&num_can_eat_lock);
	num_can_eat++;
	pthread_mutex_unlock (&num_can_eat_lock);
}