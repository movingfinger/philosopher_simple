/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 10:55:32 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 07:23:15 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long timer(void)
{
	static struct timeval var;
	long long time;

	gettimeofday(&var, NULL);
	time = var.tv_sec * (long long )1000 + var.tv_usec / 1000;
	return (time);
}