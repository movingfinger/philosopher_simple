/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/06/13 12:00:24 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	int i;
	int death;
	int num_test;

	set_param(av, ac);
	sem_close(sem_open("SEM", O_CREAT, S_IRWXO, num_philo));
	i = num_philo;
	death = num_philo;
	num_test = num_philo;
	if (!i)
		exit(0);
	while (i > 0)
	{
		Spawn(&num_test, &death);
		i--;
	}
	return (0);
}