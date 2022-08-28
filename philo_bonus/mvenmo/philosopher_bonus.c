/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:30:51 by mvenmo            #+#    #+#             */
/*   Updated: 2022/03/05 14:12:49 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(env->print_sem);
	printf("%ld %d %s\n", current_time() - env->start_time, id + 1, status);
	sem_post(env->print_sem);
}

void	philosopher(t_env *env)
{
	int		id;

	id = env->id;
	while (1)
	{
		sem_wait(env->garcon_sem);
		sem_wait(env->forks);
		ft_message(env, id, "has taken a fork");
		sem_wait(env->forks);
		sem_post(env->garcon_sem);
		sem_wait(env->eat_sem);
		ft_message(env, id, "has taken a fork");
		env->die_at = current_time() + env->time_to_die;
		if (env->n_times_to_eat > 0)
			env->n_times_to_eat--;
		ft_message(env, id, "is eating");
		sem_post(env->eat_sem);
		usleep(env->time_to_eat);
		sem_post(env->forks);
		sem_post(env->forks);
		ft_message(env, id, "is sleeping");
		usleep(env->time_to_sleep);
		ft_message(env, id, "is thinking");
	}
}

void	*ft_monitoring(void *arg)
{
	t_env	*env;

	env = (t_env *)arg;
	while (1)
	{
		usleep(3000);
		sem_wait(env->eat_sem);
		if (current_time() > env->die_at)
		{
			sem_wait(env->print_sem);
			if (current_time() > env->die_at)
				printf("%ld %d died\n", current_time() - env->start_time,
					env->id + 1);
			while (env->n--)
				sem_post(env->all_eat_sem);
			exit(0);
		}
		if (env->n_times_to_eat != -1 && env->n_times_to_eat == 0)
		{
			sem_post(env->all_eat_sem);
			env->n_times_to_eat = -1;
		}
		sem_post(env->eat_sem);
	}
}

int	ft_processes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->n)
	{
		env->id = i;
		env->pid[i] = fork();
		if (env->pid[i] == -1)
		{
			while (i--)
				kill(env->pid[i], SIGTERM);
			return (1 + ft_before_after(env, 1));
		}
		if (env->pid[i] == 0)
		{
			pthread_create(&env->th, NULL, &ft_monitoring, env);
			pthread_detach(env->th);
			philosopher(env);
			exit(0);
		}
		i++;
	}
	return (0);
}
