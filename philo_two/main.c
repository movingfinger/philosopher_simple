/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 08:08:59 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int i;
	long time_basic;
	pthread_t t_time;
	sem_t sem;

	t_philosophers *t_philo;

	set_param(av, ac);
	time_basic = 0;
	t_philo = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philo);
	timestamp = (long long *)malloc(sizeof(long long) * num_philo);
	for (int j = 0; j < num_philo; j++)
		timestamp[j] = 0;
	sem_init(&sem, 0, num_philo);

	pthread_create(&t_time, NULL, timer, &time_basic);
	for (i = 0; i < num_philo; i++)
		Spawn(&t_philo[i], &sem, &time_basic, i);
	for (i = 0; i < num_philo; i++)
	{
		pthread_join (t_philo[i].thread_philo, NULL);
		pthread_join (t_philo[i].thread_philo_time, NULL);
	}
	for (i = 0; i < num_philo; i++)
		if (t_philo[i].eat_count)
			 check_food += t_philo[i].eat_count;
	if (!check_food)
		printf("All philosophers are happy now!\n");
	sem_destroy(&sem);
	return (0);
}
