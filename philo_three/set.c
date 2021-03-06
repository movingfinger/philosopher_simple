/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 18:18:01 by sako              #+#    #+#             */
/*   Updated: 2020/06/26 18:11:25 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
**	If number of philosophers is over 100, print error and exit.
*/

void error_check(char **arg)
{
	if (ft_atol(arg[1]) > 100)
		ft_print_error(ERR_NUMMAX);
	for (int i = 2; arg[i]; i++)
	{
		if (arg[i][0] == '-')
			ft_print_error(ERR_NEG);
		if (ft_atol(arg[i]) > __INT_MAX__)
			ft_print_error(ERR_INTMAX);
		for (int j = 0; arg[i][j]; j++)
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				ft_print_error(ERR_NONUM);
		}
	}
}

void set_param(char **av, int ac)
{
	
	if (ac > 6 || ac < 5)
		ft_print_error(ERR_ARG);
	else if(ac == 5)
		food_limit = -1;
	else if (ac == 6)
		food_limit = ft_atol(av[5]);
	error_check(av);
	num_philo = ft_atol(av[1]);
	if (num_philo == 0)
		ft_print_error("No philosopher there!");
	die_seconds = ft_atol(av[2]);
	eat_seconds = ft_atol(av[3]);
	sleep_seconds = ft_atol(av[4]);
	
	printf("Number of philosopher is %lld\n", num_philo);
	printf("Die time is %lld ms\n", die_seconds);
	printf("Eat time is %lld ms\n", eat_seconds);
	printf("Sleep time is %lld ms\n", sleep_seconds);
	if (food_limit == -1)
		printf("food is unlimited\n");
	else
		printf("food limit is %lld\n", food_limit);
}

sem_t	*ft_sem_open(const char *str, int num)
{
	return (sem_open(str, O_CREAT | O_EXCL, 0644, num));
}

int init_philo(t_philosophers *philo)
{
	int		i;
	char	*c_sem;

	i = 0;
	while (i < num_philo)
	{
		philo[i].state  = 3;
		philo[i].pos = i;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % num_philo;
		c_sem = make_semaphore("SEM_PHILO", i);
		if (!(philo[i].sem = ft_sem_open(c_sem, 1)))
			ft_print_error("Failed to generate philo semaphore!");
		c_sem = make_semaphore("SEM_FOOD", i);
		if (!(philo[i].food_count = ft_sem_open(c_sem, 0)))
			ft_print_error("Failed to generate food limit semaphore!");
		i++;
		free(c_sem);
	}
	return (0);
}

int init_semaphore(void)
{
	sem_unlink("SEM_FORK");
	sem_unlink("SEM_PRINT");
	sem_unlink("SEM_DEAD");
	sem_unlink("SEM_DEAD_REPORT");
	if (!(sem_fork = ft_sem_open("SEM_FORK", num_philo)))
		ft_print_error("Fail to make semaphore for forks");
	if (!(sem_print = ft_sem_open("SEM_PRINT", 1)))
		ft_print_error("Fail to make semaphore for print");
	if (!(sem_dead = ft_sem_open("SEM_DEAD", 0)))
		ft_print_error("Fail to make semaphore for dead count");
	if (!(sem_dead_report = ft_sem_open("SEM_DEAD_REPORT", 1)))
		ft_print_error("Fail to make semaphore for report dead");	
	return (0);
}

int clear_philosopher(t_philosophers *philo)
{
	int	i;

	i = 0;
	sem_unlink("SEM_FORK");
	sem_unlink("SEM_PRINT");
	sem_unlink("SEM_DEAD");
	sem_unlink("SEM_DEAD_REPORT");
	if (philo)
	{
		i = 0;
		while (i < num_philo)
		{
			make_semaphore("SEM_PHILO", i);
			make_semaphore("SEM_FOOD", i);
			i++;
		}
		free(philo);
	}
	return (1);
}
