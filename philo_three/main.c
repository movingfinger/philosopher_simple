/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sako <sako@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:39:57 by sako              #+#    #+#             */
/*   Updated: 2020/06/17 20:31:52 by sako             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*make_semaphore(const char *str, int i)
{
	char	*c_sem;
	char	*pos;
	int		len;

	pos = ft_ltoa_base(i, 10);
	len = ft_strlen(str) + ft_strlen(pos);
	c_sem = (char *)malloc(sizeof(char) * len);
	memset(c_sem, 0, len);
	ft_strlcat(c_sem, str, len);
	ft_strlcat(c_sem, pos, len);
	sem_unlink(c_sem);
	//if (!(ft_sem_open(c_sem, i)))
	//{
	//	free(c_sem);
	//	free(pos);
	//	return (NULL);
	//}	
	free(pos);
	return (c_sem);
}

void get_message(int num)
{
	if (num == 0)
		printf(" is eating\n");
	else if (num == 1)
		printf(" is thinking\n");
	else if (num == 2)
		printf(" is sleeping\n");
	else if (num == 5)
		printf(" has taken a fork\n");
	else if (num == 8)
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
	printf("%lld\t", timer() - start_time);
	//if (num == 0)
	if (num != 8)
		printf("%d", philo->pos + 1);
	get_message(num);
	if (num < 4)
		sem_post(sem_dead_report);
	sem_post(sem_print);
}

void *check_count(void *t_philo)
{
	int	total;
	int	i;
	t_philosophers *philo;

	total = 0;
	philo = (t_philosophers *)t_philo;
	printf("food limit is %lld\n", food_limit);
	while (total < food_limit)
	{
		i = 0;
		while (i < num_philo)
		{
			sem_wait(philo[i].food_limit);
			i++;
		}
		total++;
	}
	print_message(philo, 8);
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
	printf("done check thread\n");
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

	t_philo = philo;
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
		print_message(philo, 1);
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
	printf("done begin process\n");
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
	ft_print_error("Clear philosopher!!");
	return (1);
}


static int init_philo(t_philosophers *philo)
//int init_philo(t_philosophers *philo)
{
	int		i;
	char	*c_sem;

	i = 0;
	while (i < num_philo)
	{
		philo[i].state  = 1;
		philo[i].pos = i;
		philo[i].lfork = i;
		philo[i].rfork = (i + 1) % num_philo;
		c_sem = make_semaphore("SEM_PHILO", i);
		if (!(philo[i].sem = ft_sem_open(c_sem, 1)))
			ft_print_error("Failed to generate philo semaphore!");
		c_sem = make_semaphore("SEM_FOOD", i);
		if (!(philo[i].food_limit = ft_sem_open(c_sem, 0)))
			ft_print_error("Failed to generate food limit semaphore!");
		i++;
	}
	free(c_sem);
	printf("done semephore\n");
	return (0);
}

static int init_semaphore(void)
//int init_semaphore(void)
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