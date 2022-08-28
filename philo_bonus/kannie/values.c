/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:09:41 by kannie            #+#    #+#             */
/*   Updated: 2022/07/26 22:17:31 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	values_waiter(char *str[], t_waiter *waiter)
{
	int	i;

	i = 0;
	waiter->must_eat = 0;
	waiter->sigone_p = 0;
	waiter->nbr_philo = ft_atoi(str[1]);
	if (waiter->nbr_philo < 1)
		return (-1);
	if (waiter->nbr_philo == 1)
		waiter->sigone_p = 1;
	waiter->time_to_life = ft_atoi(str[2]);
	if (waiter->time_to_life < 1)
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
	init_sem(waiter);
	return (0);
}

void	values_philo(t_waiter *waiter, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->nbr_eat = 0;
	philo->start = waiter->start;
	philo->last_eat = philo->start;
	philo->time_to_life = waiter->time_to_life;
	philo->time_to_eat = waiter->time_to_eat;
	philo->time_to_sleep = waiter->time_to_sleep;
	philo->print = waiter->print;
	philo->forks = waiter->forks;
	philo->kill = waiter->kill;
	philo->must_eat = waiter->must_eat;
	philo->sigone_p = waiter->sigone_p;
}

void	init_sem(t_waiter *waiter)
{
	int	i;

	i = -1;
	sem_unlink("sem_forks");
	sem_unlink("sem_print");
	sem_unlink("sem_kill");
	waiter->forks = sem_open("sem_forks", O_CREAT, 0, waiter->nbr_philo);
	waiter->kill = sem_open("sem_kill", O_CREAT, 0, waiter->nbr_philo);
	waiter->print = sem_open("sem_print", O_CREAT, 0, 1);
	while (++i < waiter->nbr_philo)
		sem_wait(waiter->kill);
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
