/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 22:32:32 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *check_count(void *t_philo)
{
	int	total;
	int	i;
	t_philosophers *philo;

	total = 0;
	philo = (t_philosophers *)t_philo;
	while (total < food_limit)
	{
		i = 0;
		while (i < num_philo)
		{
			sem_wait(philo[i].food_count);
			i++;
		}
		total++;
	}
	print_message(&philo[0], 5);
	sem_post(sem_dead);
	return ((void *)0);
}

int check_thread(t_philosophers *philo)
{
	pthread_t	tid;

	if (food_limit > -1)
	{
		if (pthread_create(&tid, NULL, &check_count, (void *)philo) != 0)
			ft_print_error("Failed to creata check thread!");
		pthread_detach(tid);
	}
	return (0);
}

void *check_process(void *t_philo)
{
	t_philosophers *philo;

	philo = (t_philosophers *)t_philo;
	while (1)
	{
		sem_wait(philo->sem);
		// If some philosopher failed to eat, then die.
		if (!(philo->state == 0) && timer() > philo->limit)
		{
			print_message(philo, 4);
			sem_post(philo->sem);
			sem_post(sem_dead);
			return ((void *)0);
		}
		sem_post(philo->sem);
		usleep(1000);
	}
	return ((void *)0);
}

int do_process(t_philosophers *philo)
{
	t_philosophers	*t_philo;
	pthread_t		tid;

	t_philo = (t_philosophers *)philo;
	t_philo->last_time = timer();
	t_philo->limit = t_philo->last_time + die_seconds;
	if (pthread_create(&tid, NULL, &check_process, philo) != 0)
		ft_print_error("Failed to generate thread for process!");
	pthread_detach(tid);
	while (1)
	{
		grab_forks(philo);
		eat(philo);
		drop_forks(philo);
		print_message(philo, 3);
	}
}

static int begin_process(t_philosophers *philo)
{
	int		i;

	start_time = timer();
	i = 0;
	while (i < num_philo)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			ft_print_error("Failed to fork child process!");
		else if (philo[i].pid == 0)
		{
			do_process(&philo[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	int i;
	t_philosophers *philo;

	set_param(av, ac);
	if (!(philo = (t_philosophers *)malloc(sizeof(t_philosophers) * num_philo)))
		ft_print_error("Fail to generate philosopher structure!");
	if (init_philo(philo))
		ft_print_error("Fail to initialize philo structure!");
	if (init_semaphore() || check_thread(philo) || begin_process(philo))
		return (clear_philosopher(philo));
	sem_wait(sem_dead);
	i = 0;
	while (i < num_philo)
		kill(philo[i++].pid, SIGKILL);
	clear_philosopher(philo);
	return (0);
}