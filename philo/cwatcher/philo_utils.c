/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:45:02 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/27 16:36:27 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include "main.h"

time_t	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_sleep(t_g *g, time_t	milliseconds)
{
	time_t	end;
	int		r;

	end = now() + milliseconds;
	if (now() < end - 20)
		usleep(milliseconds - 20);
	while (now() < end && !g->simulation_should_stop)
	{
		r = usleep(500);
		if (r != 0)
			return (r);
	}
	return (0);
}

// Supposed that g.sync_mutex is locked

t_bool	philo_must_stop(t_philo *philo)
{
	t_g *const	g = philo->g;

	if (g->simulation_should_stop)
	{
		pthread_mutex_unlock(&g->sync_mutex);
		return (true);
	}
	philo->timestamp = now() - g->beginning;
	if (philo->timestamp - philo->eating_timestamp > g->time_to_die)
	{
		printf("%ld %d died\n", philo->timestamp, philo->id);
		g->someone_died = true;
		if (!g->simulation_should_stop)
		{
			pthread_mutex_lock(&g->simulation_should_stop_mutex);
			pthread_mutex_unlock(&g->simulation_should_stop_mutex);
		}
		pthread_mutex_unlock(&g->sync_mutex);
		return (true);
	}
	return (false);
}
