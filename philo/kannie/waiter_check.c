/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:55:46 by kannie            #+#    #+#             */
/*   Updated: 2022/06/22 17:55:08 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	waiter_check(t_waiter *waiter)
{
	int	i;
	int	num_ate;

	i = 0;
	num_ate = 0;
	while (i < waiter->nbr_philo && waiter->s_die == 0)
	{
		pthread_mutex_lock(&waiter->print_mutx);
		if (waiter->must_eat > 0)
			if (waiter->must_eat <= waiter->philo[i].nbr_eat)
				num_ate++;
		if ((time_to() - waiter->philo[i].last_eat) > waiter->time_to_die)
		{
			waiter->s_die = 1;
			waiter->philo[i].f_kill = 1;
			printf("%lld %d\033[0;31m died\e[0m\n",
				(time_to() - waiter->philo[i].start), waiter->philo[i].id);
		}
		pthread_mutex_unlock(&waiter->print_mutx);
		i++;
	}
	if (num_ate == waiter->nbr_philo)
		waiter->sig_eat = 1;
}

void	waiter_philo(t_waiter *waiter)
{
	int	i;

	i = -1;
	while (1)
	{
		if (waiter->sig_eat == 0)
			waiter_check(waiter);
		if (waiter->sig_eat == 1 || waiter->s_die == 1)
			break ;
	}
	pthread_mutex_lock(&waiter->print_mutx);
	while (++i < waiter->nbr_philo)
	{
		if (waiter->philo[i].f_kill == 0)
			waiter->philo[i].f_kill = 1;
	}
	pthread_mutex_unlock(&waiter->print_mutx);
}

void	check_1_philo(t_philo *philo)
{
	ft_sleep_philo((philo->time_to_die + 1), philo);
	pthread_mutex_unlock(philo->left_fork);
}
