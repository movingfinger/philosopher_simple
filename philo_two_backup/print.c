/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:39:41 by sako              #+#    #+#             */
/*   Updated: 2020/06/27 14:53:52 by sako             ###   ########.fr       */
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

	if (sem_wait(philo->status->sem_message) != 0)
		ft_print_error("Failed to wait message!");
	if (finish == 0)
	{
		printf("%lld\t", timer() - philo->status->start_time);
		if (stat != ST_DONE)
			printf("%d", philo->id + 1);
		if (stat >= ST_DIE)
			finish = 1;
		if (stat == ST_EAT)
				printf(" is eating\n");
		else if (stat == ST_SLEEP)
				printf(" is sleeping\n");
		else if (stat == ST_THINK)
				printf(" is thinking\n");
		else if (stat == ST_FORK)
				printf(" has taken a fork\n");
		else if (stat == ST_DIE)
				printf(" died\n");
		else if (stat == ST_DONE)
				printf(" finished to eat given food\n");
	}
	sem_post(philo->status->sem_message);
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
	if (pos)
		free(pos);
	return (c_sem);
}