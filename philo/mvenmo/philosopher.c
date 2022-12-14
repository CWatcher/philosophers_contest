/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:30:51 by mvenmo            #+#    #+#             */
/*   Updated: 2022/03/01 14:36:07 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	current_time(void)
{
	struct timeval	tv;
	long			time_in_milliseconds;

	gettimeofday(&tv, NULL);
	time_in_milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_milliseconds);
}

static void	ft_message(t_env *env, int id, char	*status)
{
	pthread_mutex_lock(&env->print_mutex);
	if (!env->stop)
		printf("%ld %d %s\n", current_time() - env->start_time, id + 1, status);
	pthread_mutex_unlock(&env->print_mutex);
}

static int	take_forks_and_eat(t_env *env, int id, int m1, int m2)
{
	pthread_mutex_lock(&env->forks[m1]);
	ft_message(env, id, "has taken a fork");
	if (env->n == 1)
		return (1);
	pthread_mutex_lock(&env->forks[m2]);
	pthread_mutex_lock(&env->ph[id].eat_mutex);
	ft_message(env, id, "has taken a fork");
	env->ph[id].die_at = current_time() + env->time_to_die;
	env->ph[id].times_to_eat++;
	ft_message(env, id, "is eating");
	pthread_mutex_unlock(&env->ph[id].eat_mutex);
	if (!env->stop)
		usleep(env->time_to_eat);
	pthread_mutex_unlock(&env->forks[m1]);
	pthread_mutex_unlock(&env->forks[m2]);
	return (0);
}

void	*philosopher(void *arg)
{
	int		id;
	int		m1;
	int		m2;
	t_env	*env;
	t_phil	*ph;

	ph = (t_phil *)arg;
	env = (t_env *)ph->env_address;
	id = ph->id;
	m1 = (id + id % 2) % env->n;
	m2 = (id + 1 - id % 2) % env->n;
	while (!env->stop)
	{
		if (take_forks_and_eat(env, id, m1, m2) != 0)
			return (NULL);
		ft_message(env, id, "is sleeping");
		if (!env->stop)
			usleep(env->time_to_sleep);
		ft_message(env, id, "is thinking");
	}
	return (arg);
}
