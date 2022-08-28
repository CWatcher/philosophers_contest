/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:44:56 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/28 23:15:50 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "main.h"
#include "utils.h"

static t_bool	philo_take_fork(t_philo *philo, t_fork *fork)
{
	t_g *const	g = philo->g;

	pthread_mutex_lock(&fork->mutex);
	while (!fork->is_free && !g->simulation_should_stop
		&& now() - g->beginning - philo->eating_timestamp <= g->time_to_die)
		usleep(100);
	fork->is_free = false;
	pthread_mutex_unlock(&fork->mutex);
	pthread_mutex_lock(&g->sync_mutex);
	if (philo_must_stop(philo))
		return (false);
	printf("%ld %d has taken a fork\n", now() - g->beginning, philo->id);
	pthread_mutex_unlock(&g->sync_mutex);
	return (true);
}

static t_bool	philo_eat(t_philo *philo)
{
	t_g *const	g = philo->g;

	pthread_mutex_lock(&g->sync_mutex);
	philo->eating_timestamp = now() - g->beginning;
	if (philo_must_stop(philo))
		return (false);
	printf("%ld %d is eating\n", philo->eating_timestamp, philo->id);
	pthread_mutex_unlock(&g->sync_mutex);
	ft_sleep(g, philo->eating_timestamp + philo->g->time_to_eat
		- now() + g->beginning);
	philo->fork2->is_free = true;
	philo->fork1->is_free = true;
	return (true);
}

static t_bool	philo_sleep(t_philo *philo)
{
	t_g *const	g = philo->g;

	pthread_mutex_lock(&g->sync_mutex);
	g->c_well_fed_philos += ++philo->c_eating_times == g->n_times_to_eat;
	if (g->c_well_fed_philos == g->n_philos
		&& pthread_mutex_lock(&g->simulation_should_stop_mutex) == 0)
		pthread_mutex_unlock(&g->simulation_should_stop_mutex);
	philo->timestamp = now() - g->beginning;
	if (philo_must_stop(philo))
		return (false);
	philo->time_to_die = g->time_to_die;
	philo->time_to_die -= philo->timestamp - philo->eating_timestamp;
	philo->time_to_sleep = min(philo->time_to_die, g->time_to_sleep);
	printf("%ld %d is sleeping\n", philo->timestamp, philo->id);
	pthread_mutex_unlock(&g->sync_mutex);
	ft_sleep(g, philo->timestamp + philo->time_to_sleep - now() + g->beginning);
	return (true);
}

static t_bool	philo_think(t_philo *philo)
{
	t_g *const	g = philo->g;

	pthread_mutex_lock(&g->sync_mutex);
	if (philo_must_stop(philo))
		return (false);
	printf("%ld %d is thinking\n", now() - g->beginning, philo->id);
	pthread_mutex_unlock(&g->sync_mutex);
	return (true);
}

void	*philo_run(void *arg)
{
	t_philo *const	philo = arg;
	t_g *const		g = philo->g;

	if (g->n_philos_is_even)
	{
		pthread_mutex_lock(&g->start_mutex);
		pthread_mutex_unlock(&g->start_mutex);
	}
	while (philo_take_fork(philo, philo->fork1)
		&& philo_take_fork(philo, philo->fork2)
		&& philo_eat(philo)
		&& philo_sleep(philo)
		&& philo_think(philo))
		;
	return (NULL);
}
