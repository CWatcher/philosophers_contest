/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:44:38 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/27 17:01:30 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "utils.h"
#include "ft_limits.h"

int	main(int argc, char *argv[])
{
	t_g		g;
	t_fork	*forks;
	t_philo	*philos;
	int		i;

	forks = NULL;
	philos = NULL;
	if (argc < 5 || argc > 6 || !read_args(&g, argc, argv))
	{
		ft_putstr_fd("Error\nWrong or unsupported arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!alloc(&forks, &philos, g.n_philos) || !init(&g, forks, philos))
		return (clean(&g, forks, philos, 2));
	pthread_mutex_lock(&g.simulation_should_stop_mutex);
	if (!start(&g, philos))
		return (clean(&g, forks, philos, 3));
	while (!g.simulation_should_stop)
		if (g.someone_died || g.c_well_fed_philos >= g.n_philos)
			g.simulation_should_stop = true;
	pthread_mutex_unlock(&g.simulation_should_stop_mutex);
	i = -1;
	while (++i < g.n_philos)
		pthread_join(philos[i].th, NULL);
	clean(&g, forks, philos, 0);
}

t_bool	start(t_g *g, t_philo *philos)
{
	if (g->n_philos_is_even || g->n_philos == 1)
		return (start_even(g, philos));
	else
		return (start_odd(g, philos));
}

t_bool	start_even(t_g *g, t_philo *philos)
{
	int	order;
	int	i;

	if (g->n_times_to_eat == 0)
		return (true);
	pthread_mutex_lock(&g->start_mutex);
	order = 0;
	while (order < 2)
	{
		i = order;
		while (i < g->n_philos)
		{
			if (pthread_create(&philos[i].th, NULL, philo_run, &philos[i]) != 0)
				return (false);
			i += 2;
		}
		if (order++ == 0)
		{
			g->beginning = now();
			pthread_mutex_unlock(&g->start_mutex);
		}
		ft_sleep(g, g->time_to_eat / 2);
	}
	return (true);
}

t_bool	start_odd(t_g *g, t_philo *philos)
{
	int	order;
	int	i;

	if (g->n_times_to_eat == 0)
		return (true);
	order = 0;
	g->start_interval = g->time_to_eat / (g->n_philos / 2);
	g->beginning = now();
	while (order < 2)
	{
		i = order;
		while (i < g->n_philos)
		{
			if (pthread_create(&philos[i].th, NULL, philo_run, &philos[i]) != 0)
				return (false);
			if (order == 0 && i < g->n_philos - 1)
				ft_sleep(g, g->start_interval);
			i += 2;
		}
		order++;
	}
	return (true);
}
