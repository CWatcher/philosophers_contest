/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 15:55:46 by kannie            #+#    #+#             */
/*   Updated: 2022/06/24 17:54:31 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_check(void *buf)
{
	t_philo	*philo;

	philo = (t_philo *)buf;
	while (1)
	{
		sem_wait(philo->print);
		if ((time_to() - philo->last_eat) > philo->time_to_life)
		{
			printf("%lld %d\033[0;31m died\e[0m\n",
				(time_to() - philo->start), philo->id);
			while (1)
				sem_post(philo->kill);
			return (NULL);
		}
		sem_post(philo->print);
	}
}

void	check_ate(t_waiter *waiter)
{
	int			i;

	i = -1;
	while (++i < waiter->nbr_philo)
		sem_wait(waiter->kill);
	i = -1;
	while (++i < waiter->nbr_philo)
		kill(waiter->philo[i].pid_id, SIGTERM);
}
