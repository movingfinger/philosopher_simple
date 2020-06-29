/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:59:28 by sako              #+#    #+#             */
/*   Updated: 2020/06/26 10:01:56 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long ft_atol (const char *str)
{
	int i;
	long long res;

	i = 0;
	res = 0;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		++i;
	}
	if (str[i] != '\0')
		return (-1);
	return (res);
}

long long timer(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (long long)1000 + time.tv_usec / 1000);
}