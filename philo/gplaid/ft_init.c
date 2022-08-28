/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:33:27 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 16:47:37 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*set_fork(int i, t_philo *philo, pthread_mutex_t *fork_mutex)
{
	philo[i].first_fork = fork_mutex + i;
	philo[i].second_fork = fork_mutex;
	while (i--)
	{
		philo[i].first_fork = fork_mutex + i;
		philo[i].second_fork = fork_mutex + i + 1;
	}
	return (philo);
}

static t_philo	*init_philo(int argc, int *value, pthread_mutex_t *fork_mutex)
{
	t_philo	*philo;
	int		i;

	i = value[0];
	philo = (t_philo *)malloc(sizeof(t_philo) * i);
	if (!philo)
		return (NULL);
	while (i--)
	{
		philo[i].id = i + 1;
		philo[i].value = value;
		philo[i].ut0 = ft_get_time();
		philo[i].arg5 = NULL;
		if (argc == ARG5)
			philo[i].arg5 = value + 4;
		pthread_mutex_init(fork_mutex + i, NULL);
	}
	if (argc == ARG5)
		value[4] *= value[0];
	return (set_fork(value[0] - 1, philo, fork_mutex));
}

static void	create_philo(const int *value, t_philo *philo, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < value[0])
	{
		pthread_create(threads + i, NULL, ft_philo, (void *)(philo + i));
		i += 2;
		if (i >= value[0] && !(i % 2))
			i = 1;
	}
}

static int	start_philo(int *value, pthread_mutex_t *fork_mutex, t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * (value[0] + 1));
	if (!threads)
		return (0);
	create_philo(value, philo, threads);
	pthread_create(threads + value[0], NULL, ft_watcher, (void *) philo);
	i = 0;
	while (i < value[0])
		pthread_join(threads[i++], NULL);
	pthread_join(threads[value[0]], NULL);
	while (i--)
		pthread_mutex_destroy(fork_mutex + i);
	free(threads);
	return (1);
}

int	ft_init(int argc, int *value)
{
	pthread_mutex_t	*fork_mutex;
	t_philo			*philo;

	fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * value[0]);
	if (!fork_mutex)
		return (ft_free(value, NULL, NULL));
	philo = init_philo(argc, value, fork_mutex);
	if (!philo)
		return (ft_free(value, fork_mutex, NULL));
	if (!start_philo(value, fork_mutex, philo))
		return (ft_free(value, fork_mutex, philo));
	return (1);
}
