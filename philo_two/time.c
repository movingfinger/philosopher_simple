/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:55:32 by sako              #+#    #+#             */
/*   Updated: 2020/06/11 12:53:49 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *timer(void *var)
{
	struct timeval time;
	struct timeval time2;
	long *elapsed;

	elapsed = var;
	gettimeofday(&time, NULL);
	while (1)
	{
		gettimeofday(&time2, NULL);
		*elapsed = (((time2.tv_sec - time.tv_sec) * 1000 + ((time2.tv_usec - time.tv_usec) / 1000)));
		if (*elapsed < 0)
			*elapsed *= -1;
	}
}

void *philo_life(void *arg)
{
	t_philosophers *philo;
	struct timeval time;
	struct timeval time2;
	long long elapsed;

	philo = arg;
	gettimeofday(&time, NULL);
	elapsed = 0;
	while (1)
	{
		gettimeofday(&time2, NULL);
		elapsed = (((time2.tv_sec - time.tv_sec) * 1000 + ((time2.tv_usec - time.tv_usec) / 1000)));
		timestamp[philo->pos] = *philo->time;
		if (die_seconds <= elapsed)
		{			
			philo->state = 3;
			printf("%lld ms - Philosopher %d died due to timeover\n", timestamp[philo->pos], philo->pos);
			exit (0);
		}
		if (philo->state == 0)
			pthread_exit(NULL);
	}
}