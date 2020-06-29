/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/06/26 18:11:28 by sako             ###   ########.fr       */
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

char	*make_semaphore(const char *str, int i)
{
	char	*c_sem;
	char	*pos;
	int		len;

	pos = ft_ltoa_base(i, 10);
	len = ft_strlen(str) + ft_strlen(pos);
	c_sem = ft_strnew(len);
	ft_strlcat(c_sem, str, len);
	ft_strlcat(c_sem, pos, len);
	sem_unlink(c_sem);
	if (pos)
		free(pos);
	return (c_sem);
}