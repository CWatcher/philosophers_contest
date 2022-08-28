/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:09:41 by kannie            #+#    #+#             */
/*   Updated: 2022/05/24 15:11:41 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	values_waiter(char *str[], t_waiter *waiter)
{
	int	i;

	i = 0;
	waiter->nbr_philo = ft_atoi(str[1]);
	if (waiter->nbr_philo < 1)
		return (-1);
	waiter->time_to_die = ft_atoi(str[2]);
	if (waiter->time_to_die < 1)
		return (-1);
	waiter->time_to_eat = ft_atoi(str[3]);
	if (waiter->time_to_eat < 1)
		return (-1);
	waiter->time_to_sleep = ft_atoi(str[4]);
	if (waiter->time_to_sleep < 1)
		return (-1);
	if (str[5])
		i = num_portion(str[5], waiter);
	if (i < 0)
		return (i);
	i = init_mut(waiter);
	if (i < 0)
		return (i);
	return (0);
}

void	values_philo(t_waiter *waiter, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->nbr_eat = 0;
	if (waiter->nbr_philo == 1)
	{
		philo->time_to_die = waiter->time_to_die;
		philo->nbr_philo = 1;
	}
	philo->start = waiter->start;
	philo->last_eat = philo->start;
	philo->time_to_eat = waiter->time_to_eat;
	philo->time_to_sleep = waiter->time_to_sleep;
	philo->f_kill = waiter->s_die;
	philo->print_mutx = &waiter->print_mutx;
	philo->left_fork = &waiter->forks[i];
	if (philo->id == waiter->nbr_philo)
		philo->right_fork = &waiter->forks[0];
	else
		philo->right_fork = &waiter->forks[i + 1];
}

int	init_mut(t_waiter *waiter)
{	
	int	i;

	i = -1;
	waiter->sig_eat = 0;
	waiter->forks = malloc (sizeof(pthread_mutex_t) * waiter->nbr_philo);
	if (!waiter->forks)
		return (i);
	while (++i < waiter->nbr_philo)
		pthread_mutex_init(&waiter->forks[i], NULL);
	pthread_mutex_init(&waiter->print_mutx, NULL);
	return (0);
}

int	num_portion(char *str, t_waiter *waiter)
{
	waiter->must_eat = ft_atoi(str);
	if (waiter->must_eat == 0)
		return (-2);
	if (waiter->must_eat <= -1)
		return (-1);
	return (0);
}
