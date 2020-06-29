/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:18:01 by sako              #+#    #+#             */
/*   Updated: 2020/06/27 21:32:00 by sako             ###   ########.fr       */
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

void init_semaphore(t_status *status)
{
	if (!(status->sem_fork = ft_sem_open("SEM_FORK", status->num_philo)))
		ft_print_error("Fail to make semaphore for forks");
	if (!(status->sem_message = ft_sem_open("SEM_MESSAGE", 1)))
		ft_print_error("Fail to make semaphore for print");
	if (!(status->sem_dead = ft_sem_open("SEM_DEAD", 0)))
		ft_print_error("Fail to make semaphore for dead count");
}

void init_philo(t_status *status)
{
	int		i;
	char	*c_sem;

	if (!(status->philo =
		(t_philosophers *)malloc(sizeof(t_philosophers) * status->num_philo)))
			ft_print_error("Failed to assign philosopher memory!");
	for (i = 0; i < status->num_philo; i++)
	{
		status->philo[i].id = i;
		status->philo[i].eat_count = 0;
		status->philo[i].is_eating = 0;
		status->philo[i].l_fork = i;
		status->philo[i].r_fork = (i + 1) % status->num_philo;
		status->philo[i].status = status;
		c_sem = make_semaphore("SEM_PHILO", i);
		if (!(status->philo[i].sem_mutex = ft_sem_open(c_sem, 1)))
			ft_print_error("Failed to generate philo semaphore!");
		c_sem = make_semaphore("SEM_FOOD", i);
		if (!(status->philo[i].sem_eat = ft_sem_open(c_sem, 0)))
			ft_print_error("Failed to generate food limit semaphore!");
	}
	if (c_sem)	
		free(c_sem);
}

void set_param(int ac, char **av, t_status *status)
{
	status->num_philo = ft_atol(av[1]);
	status->time_to_die = ft_atol(av[2]);
	status->time_to_eat = ft_atol(av[3]);
	status->time_to_sleep = ft_atol(av[4]);
	status->sem_fork = NULL;
	status->philo = NULL;
	if (ac > 6 || ac < 5)
		ft_print_error(ERR_ARG);
	else if(ac == 5)
		status->must_eat = 0;
	else if (ac == 6)
		status->must_eat = ft_atol(av[5]);
	error_check(av);
	print_input(status);
	init_philo(status);
	init_semaphore(status);
}

sem_t	*ft_sem_open(const char *str, int num)
{
	sem_unlink(str);
	return (sem_open(str, O_CREAT | O_EXCL, 0644, num));
}
