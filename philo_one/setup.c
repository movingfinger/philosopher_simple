/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:18:01 by sako              #+#    #+#             */
/*   Updated: 2020/06/25 22:42:47 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_check(char **av)
{
	if (ft_atol(av[1]) > 200 || av[1][0] == '-')
		ft_print_error(ERR_NUMMAX);
	for (int i = 2; av[i]; i++)
	{
		for (int j = 0; av[i][j]; j++)
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				ft_print_error(ERR_NONUM);
		}
		if (ft_atol(av[i]) > __INT_MAX__)
			ft_print_error(ERR_INTMAX);
	}
}

void init_mutex(t_status *status)
{
	int i;

	pthread_mutex_init(&status->m_message, NULL);
	pthread_mutex_init(&status->m_dead, NULL);
	pthread_mutex_lock(&status->m_dead);
	if (!(status->m_fork =
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * status->num_philo)))
		{
			free_status(status);
			ft_print_error("Failed to initialized fork mutex!");
		}
	for (i = 0; i < status->num_philo; i++)
		pthread_mutex_init(&status->m_fork[i], NULL);
}

void init_philo(t_status *status)
{
	int	i;

	if (!(status->philo =
		(t_philosophers *)malloc(sizeof(t_philosophers) * status->num_philo)))
		{
			free_status(status);
			ft_print_error("Failed to assign philosopher memory!");
		}
	for (i = 0; i < status->num_philo; i++)
	{
		status->philo[i].id = i;
		status->philo[i].eat_count = 0;
		status->philo[i].is_eating = 0;
		status->philo[i].l_fork = i;
		status->philo[i].r_fork = (i + 1) % status->num_philo;
		status->philo[i].status = status;
		pthread_mutex_init(&status->philo[i].m_mutex, NULL);
		pthread_mutex_init(&status->philo[i].m_eat, NULL);
		pthread_mutex_lock(&status->philo[i].m_eat);
	}
}

void set_param(int ac, char **av, t_status *status)
{
	status->num_philo = ft_atol(av[1]);
	status->start_time = timer();
	status->time_to_die = ft_atol(av[2]);
	status->time_to_eat = ft_atol(av[3]);
	status->time_to_sleep = ft_atol(av[4]);
	status->m_fork = NULL;
	status->philo = NULL;
	if (ac > 6 || ac < 5)
	{
		free_status(status);
		ft_print_error(ERR_ARG);
	}
	else if(ac == 5)
		status->must_eat = 0;
	else if (ac == 6)
		status->must_eat = ft_atol(av[5]);
	error_check(av);
	print_input(status);
	init_philo(status);
	init_mutex(status);
}