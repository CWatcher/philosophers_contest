/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:39:00 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 16:46:50 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork(t_philo *philo, int forks)
{
	if (forks)
	{
		pthread_mutex_lock(philo->first_fork);
		pthread_mutex_lock(philo->second_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->first_fork);
		pthread_mutex_unlock(philo->second_fork);
	}
}

static void	print_status(t_philo *philo, int status)
{
	long	time;

	time = ft_get_time();
	if (status == eating && philo->value[1])
	{
		printf("%li\t%d has taken a fork\n", time - philo->ut0, philo->id);
		printf("%li\t%d is eating\n", time - philo->ut0, philo->id);
		if (philo->arg5)
			(*philo->arg5)--;
		ft_usleep(philo->value[2], philo);
	}
	else if (status == sleeping && philo->value[1])
	{
		printf("%li\t%d is sleeping\n", time - philo->ut0, philo->id);
		ft_usleep(philo->value[3], philo);
		if (philo->value[1])
			printf("%li\t%d is thinking\n", time - philo->ut0, philo->id);
	}
}

static int	is_died(t_philo *philo)
{
	long	time;

	time = ft_get_time();
	if (time - philo->ut0 - philo->ut1 > philo->value[1])
	{
		philo->value[1] = 0;
		printf("\e[31m%li\t%d is dead\e[0m\n", time - philo->ut0, philo->id);
		return (0);
	}
	else if (philo->arg5 && !*philo->arg5)
	{
		philo->value[1] = 0;
		return (0);
	}
	return (1);
}

void	*ft_watcher(void *tid)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)tid;
	i = 0;
	i ^= i;
	while (!i)
	{
		while (i < philo->value[0])
			if (!is_died(philo + i++))
				pthread_exit(NULL);
		i ^= i;
	}
	pthread_exit(NULL);
}

void	*ft_philo(void *tid)
{
	t_philo	*philo;

	philo = (t_philo *)tid;
	philo->ut1 = 0;
	while (philo->value[1] && philo->value[0] != 1)
	{
		take_fork(philo, lock);
		philo->ut1 = ft_get_time() - philo->ut0;
		print_status(philo, eating);
		take_fork(philo, unlock);
		print_status(philo, sleeping);
	}
	pthread_exit(NULL);
}
