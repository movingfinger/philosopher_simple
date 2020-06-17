/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 22:37:10 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print_error(const char *str)
{
	printf("%s\n", str);
	exit (0);
}

void get_message(int num)
{
	if (num == 0)
		printf(" is eating\n");
	else if (num == 1)
		printf(" is sleeping\n");
	else if (num == 2)
		printf(" has taken a fork\n");
	else if (num == 3)
		printf(" is thinking\n");
	else if (num == 5)
		printf(" food limit reached\n");
	else
		printf(" died\n");
}

/*
**	If num is 0, print pos.
*/

void print_message(t_philosophers *philo, int num)
{
	sem_wait(sem_print);
	sem_wait(sem_dead_report);
	printf("%lld ms - Philosopher ", timer() - start_time);
	if (num != 5)
		printf("%d", philo->pos + 1);
	get_message(num);
	if (num < 4)
		sem_post(sem_dead_report);
	sem_post(sem_print);
}
