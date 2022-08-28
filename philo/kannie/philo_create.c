/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:07:18 by kannie            #+#    #+#             */
/*   Updated: 2022/06/23 18:30:28 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philo(t_waiter *waiter)
{
	int				i;

	i = -1;
	waiter->philo = malloc (sizeof(t_philo) * waiter->nbr_philo);
	if (!waiter->philo)
		return (-1);
	waiter->start = time_to();
	while (++i < waiter->nbr_philo)
	{
		values_philo(waiter, &(waiter->philo[i]), i);
		pthread_create(&waiter->philo[i].life_philo, NULL, &philo_life,
			(&waiter->philo[i]));
	}
	waiter_philo(waiter);
	i = -1;
	while (++i < waiter->nbr_philo)
		pthread_join(waiter->philo[i].life_philo, NULL);
	return (0);
}

void	*philo_life(void *buf)
{
	t_philo		*philo;

	philo = (t_philo *)buf;
	while (1)
	{
		pthread_mutex_lock(philo->print_mutx);
		if (philo->f_kill > 0)
			break ;
		pthread_mutex_unlock(philo->print_mutx);
		f_life(philo);
	}
	pthread_mutex_unlock(philo->print_mutx);
	return (NULL);
}

void	f_life(t_philo *philo)
{
	if (philo_check_dide(philo) == 1)
		return ;
	lock_fork(philo);
	pthread_mutex_lock(philo->print_mutx);
	philo->last_eat = time_to();
	pthread_mutex_unlock(philo->print_mutx);
	what_philo_do(philo, "35m is eating", philo->time_to_eat);
	if (philo_check_dide(philo) == 1)
	{
		unlock_fork(philo);
		return ;
	}
	pthread_mutex_lock(philo->print_mutx);
	philo->nbr_eat++;
	pthread_mutex_unlock(philo->print_mutx);
	unlock_fork(philo);
	if (philo_check_dide(philo) == 1)
		return ;
	what_philo_do(philo, "34m is sleeping", philo->time_to_sleep);
	if (philo_check_dide(philo) == 1)
		return ;
	what_philo_do(philo, "36m is thinking", 0);
}

void	what_philo_do(t_philo *philo, char *str, int time_to_do)
{
	if (philo_check_dide(philo) == 1)
		return ;
	pthread_mutex_lock(philo->print_mutx);
	printf("%lld %d\033[0;%s\e[0m\n", (time_to() - philo->start), philo->id, str);
	pthread_mutex_unlock(philo->print_mutx);
	if (time_to_do > 0)
		ft_sleep_philo(time_to_do, philo);
}

int	philo_check_dide(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutx);
	if (philo->f_kill > 0)
	{
		pthread_mutex_unlock(philo->print_mutx);
		return (1);
	}
	pthread_mutex_unlock(philo->print_mutx);
	return (0);
}
