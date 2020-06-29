/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/06/25 22:46:18 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_error(const char *str)
{
	printf("%s\n", str);
	exit (0);
}

void	print_input(t_status *status)
{
	printf("Die time is %lld ms\n", status->time_to_die);
	printf("Eat time is %lld ms\n", status->time_to_eat);
	printf("Sleep time is %lld ms\n", status->time_to_sleep);
	printf("Number of philosopher is %d\n", status->num_philo);
	if ( status->must_eat == 0)
		printf("food is unlimited\n");
	else
		printf("food limit per philosophers is %lld\n", status->must_eat);
}

void	print_status(t_philosophers *philo, int stat)
{
	static int finish = 0;

	pthread_mutex_lock(&philo->status->m_message);
	if (finish == 0)
	{
		printf("%lld ", timer() - philo->status->start_time);
		printf("%d", philo->id + 1);
		if (stat == ST_DIE || stat == ST_DONE)
			finish = 1;
		switch (stat)
		{
			case ST_EAT:
				printf(" is eating\n");
				break;
			case ST_SLEEP:
				printf(" is sleeping\n");
				break;
			case ST_THINK:
				printf(" is thinking\n");
				break;
			case ST_FORK:
				printf(" has taken a fork\n");
				break;
			case ST_DIE:
				printf(" died\n");
				break;
			case ST_DONE:
				printf(" finished to eat given food\n");
				break;
		}
	}
	pthread_mutex_unlock(&philo->status->m_message);
}