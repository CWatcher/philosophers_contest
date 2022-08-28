/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_routines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:44:38 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/27 17:26:03 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "utils.h"
#include "ft_limits.h"

t_bool	read_args(t_g *g, int argc, char *argv[])
{
	int		i;
	char	*s;

	*g = (t_g){0};
	i = 0;
	while (++i < argc)
	{
		s = argv[i];
		while (*s)
			if (!ft_isdigit(*s++))
				return (false);
	}
	g->n_philos = ft_atoi(argv[1]);
	g->time_to_die = ft_atoi(argv[2]);
	g->time_to_eat = min(ft_atoi(argv[3]), g->time_to_die);
	g->time_to_sleep = min(ft_atoi(argv[4]), g->time_to_die - g->time_to_eat);
	g->n_times_to_eat = LONG_MAX;
	if (argc == 6)
		g->n_times_to_eat = ft_atoi(argv[5]);
	if (g->n_philos == INT_MAX || g->time_to_die == INT_MAX
		|| g->time_to_eat == INT_MAX || g->time_to_sleep == INT_MAX
		|| (argc == 6 && g->n_times_to_eat == INT_MAX))
		return (false);
	return (true);
}

t_bool	alloc(t_fork **p_forks, t_philo **p_philos, int n_philos)
{
	*p_forks = malloc(n_philos * sizeof(t_fork));
	*p_philos = malloc(n_philos * sizeof(t_philo));
	if (!p_forks || !p_philos)
		return (false);
	return (true);
}

t_bool	init(t_g *g, t_fork *forks, t_philo *philos)
{
	int	i;

	if (g->n_philos % 2 == 0)
		g->n_philos_is_even = true;
	i = -1;
	while (++i < g->n_philos)
	{
		forks[i].is_free = true;
		philos[i] = (t_philo){0};
		philos[i].id = i + 1;
		philos[i].g = g;
		philos[i].fork1 = &forks[i];
		philos[i].fork2 = &forks[(i + 1) % g->n_philos];
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
			return (false);
	}
	philos[g->n_philos - 1].fork1 = &forks[0];
	philos[g->n_philos - 1].fork2 = &forks[g->n_philos - 1];
	if (pthread_mutex_init(&g->start_mutex, NULL) != 0
		|| pthread_mutex_init(&g->sync_mutex, NULL) != 0
		|| pthread_mutex_init(&g->simulation_should_stop_mutex, NULL) != 0)
		return (false);
	return (true);
}

int	clean(t_g *g, t_fork *forks, t_philo *philos, int error)
{
	int	i;

	i = -1;
	if (forks)
		while (++i < g->n_philos)
			pthread_mutex_destroy(&forks[i].mutex);
	pthread_mutex_destroy(&g->simulation_should_stop_mutex);
	pthread_mutex_destroy(&g->sync_mutex);
	pthread_mutex_destroy(&g->start_mutex);
	free(philos);
	free(forks);
	return (error);
}
