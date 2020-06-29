/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2020/06/19 22:20:27 by sako             ###   ########.fr       */
=======
/*   Updated: 2020/06/17 08:09:26 by sako             ###   ########.fr       */
>>>>>>> 8b0f2ab3287f884a1b03e5ae11ddd275de945a73
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
<<<<<<< HEAD
	t_status status;
	
	set_param(ac, av, &status);
	do_philosopher(&status);
=======
	int i;
	long time_basic;
	pthread_t t_time;
	t_philosophers *t_philo;

	set_param(av, ac);
	time_basic = 0;
	m_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
	t_philo = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philo);
	timestamp = (long long *)malloc(sizeof(long long) * num_philo);
	for (int j = 0; j < num_philo; j++)
		timestamp[j] = 0;
	pthread_mutex_init (&food_lock, NULL);
	pthread_mutex_init (&num_can_eat_lock, NULL);

	pthread_create(&t_time, NULL, timer, &time_basic);
	for (i = 0; i < num_philo; i++)
	{
		pthread_mutex_init (&m_fork[i], NULL);
		Spawn(&t_philo[i], &time_basic, i);
	}	
	for (i = 0; i < num_philo; i++)
	{
		pthread_join (t_philo[i].thread_philo, NULL);
		pthread_join (t_philo[i].thread_philo_time, NULL);
	}
	for (i = 0; i < num_philo; i++)
		pthread_mutex_destroy (&m_fork[i]);
	for (i = 0; i < num_philo; i++)
		if (t_philo[i].eat_count)
			 check_food += t_philo[i].eat_count;
	if (!check_food)
		printf("All philosophers are happy now!\n");
>>>>>>> 8b0f2ab3287f884a1b03e5ae11ddd275de945a73
	return (0);
}
