/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:58:10 by sako              #+#    #+#             */
/*   Updated: 2020/06/29 11:05:02 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_count(void *temp_status)
{
	t_status *status;

	status = (t_status *)temp_status;
	for (int i = 0; i < status->must_eat; i++)
		for (int j = 0; j < status->num_philo; j++)
			if (sem_wait(status->philo[j].sem_eat))
				return ((void *)0);
	if (print_status(&status->philo[0], ST_DONE))
		return ((void *)0);
	if (sem_post(status->sem_dead))
		return ((void *)0);
	return ((void *)0);
}

static void	*check_philosopher(void *t_philo)
{
	t_philosophers *philo;
	long long time;

	philo = (t_philosophers *)t_philo;
	while (1)
	{
		if (sem_wait(philo->sem_mutex) != 0)
			return ((void*)0);
		time = timer() - philo->status->start_time;
		if (!philo->is_eating && time > philo->check_time)
		{
			if (print_status(philo, ST_DIE))
				return ((void *)0);
			if (sem_post(philo->sem_mutex))
				return ((void*)0);
			if (sem_post(philo->status->sem_dead))
				return ((void*)0);
			return ((void *)0);
		}
		if (sem_post(philo->sem_mutex))
			return ((void *)0);
	}
	return ((void*)0);
}

static void	*philosopher (void *t_philo)
{
	t_philosophers	*philo;
	pthread_t		t_id;

	philo = (t_philosophers *)t_philo;
	//philo->eat_time = timer();
	philo->eat_time = timer() - philo->status->start_time;
	philo->check_time = philo->eat_time + philo->status->time_to_die;
	if (pthread_create(&t_id, NULL, check_philosopher, t_philo) != 0)
		ft_print_error("Failed to create check philosopher thread!");
	pthread_detach(t_id);
	while (1)
	{
		//get_token(philo);
		grab_fork(philo);
		eat(philo);
		down_forks(philo);
		if (print_status(philo, ST_THINK))
			return ((void *)0);
		//return_token(philo);
	}
	return ((void *)0);
}

void	do_philosopher(t_status *status)
{
	int			i;
	pthread_t	t_id;
	void		*philo;

	status->start_time = timer();
	if (status->must_eat > 0)
	{
		if (pthread_create(&t_id, NULL, &check_count, (void *)status) != 0)
			ft_print_error("Failed to make food count thread!");
		pthread_detach(t_id);
	}
	for (i = 0; i < status->num_philo; i++)
	{
		philo = (void *)(&status->philo[i]);
		if (pthread_create(&t_id, NULL, &philosopher, philo) != 0)
			ft_print_error("Failed to make philosopher thread!");
		pthread_detach(t_id);
		usleep(100);
	}
	sem_wait(status->sem_dead);
	free_status(status);
}

void	free_status(t_status *status)
{
	char *c_sem;

	sem_unlink("SEM_FORK");
	sem_unlink("SEM_MESSAGE");
	sem_unlink("SEM_DEAD");
	if (status->philo)
	{
		for (int i = 0; i < status->num_philo; i++)
		{
			c_sem = make_semaphore("SEM_PHILO", i);
			sem_unlink(c_sem);
			c_sem = make_semaphore("SEM_FOOD", i);
			sem_unlink(c_sem);
		}
		free(status->philo);
	}
	if (c_sem)
		free(c_sem);
}