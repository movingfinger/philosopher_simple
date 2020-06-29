/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diner.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 10:02:55 by sako              #+#    #+#             */
/*   Updated: 2020/06/27 21:56:49 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	eat(t_philosophers *philo)
{
	sem_wait(philo->sem_mutex);
	philo->is_eating = 1;
	philo->eat_time = timer();
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	print_status(philo, ST_EAT);
	usleep(philo->status->time_to_eat * 1000);
	philo->eat_count++;
	philo->is_eating = 0;
	sem_post(philo->sem_mutex);
	sem_post(philo->sem_eat);
}

void	grab_fork (t_philosophers *philo)
{
	sem_wait(philo->status->sem_fork);
	print_status(philo, ST_FORK);
	sem_wait(philo->status->sem_fork);
	print_status(philo, ST_FORK);
}

void	down_forks (t_philosophers *philo)
{
	print_status(philo, ST_SLEEP);
	sem_post(philo->status->sem_fork);
	sem_post(philo->status->sem_fork);
	usleep(philo->status->time_to_sleep * 1000);
}