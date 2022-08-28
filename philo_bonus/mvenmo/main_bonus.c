/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:30:51 by mvenmo            #+#    #+#             */
/*   Updated: 2022/03/05 14:30:36 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_atoi_pos(const char *str)
{
	int	res;

	res = 0;
	while (('\t' <= *str && *str <= '\r') || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			return (-1);
	while ('0' <= *str && *str <= '9')
		res = res * 10 + *str++ - '0';
	if (*str != '\0')
		return (-1);
	return (res);
}

static int	ft_args(int argc, char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (i < argc)
		if (ft_atoi_pos(argv[i++]) <= 0)
			return (1);
	env->n = ft_atoi_pos(argv[1]);
	env->time_to_die = ft_atoi_pos(argv[2]);
	env->time_to_eat = ft_atoi_pos(argv[3]) * 1000;
	env->time_to_sleep = ft_atoi_pos(argv[4]) * 1000;
	if (argc == 6)
		env->n_times_to_eat = ft_atoi_pos(argv[5]);
	else
		env->n_times_to_eat = -1;
	env->pid = malloc(env->n * sizeof(*env->pid));
	if (env->pid == NULL)
		return (1);
	return (0);
}

static sem_t	*ft_sem_init(const char *sem_name, unsigned int init_value)
{
	sem_t	*res;

	res = sem_open(sem_name, O_CREAT | O_EXCL, 0664, init_value);
	if (res == SEM_FAILED && errno == EEXIST)
	{
		sem_unlink(sem_name);
		res = sem_open(sem_name, O_CREAT | O_EXCL, 0664, init_value);
	}
	return (res);
}

int	ft_before_after(t_env *env, int mode)
{
	if (mode == 0)
	{
		env->start_time = current_time();
		env->die_at = env->start_time + env->time_to_die;
		env->print_sem = ft_sem_init("print", 1);
		env->forks = ft_sem_init("forks", env->n);
		env->garcon_sem = ft_sem_init("garcon", 1);
		env->eat_sem = ft_sem_init("eat", 1);
		env->all_eat_sem = ft_sem_init("all_eat", 0);
		if (env->print_sem == SEM_FAILED || env->forks == SEM_FAILED
			|| env->garcon_sem == SEM_FAILED || env->eat_sem == SEM_FAILED
			|| env->all_eat_sem == SEM_FAILED)
			return (1 + ft_before_after(env, 1));
	}
	else
	{
		sem_close(env->print_sem);
		sem_close(env->forks);
		sem_close(env->eat_sem);
		sem_close(env->garcon_sem);
		sem_close(env->all_eat_sem);
		free(env->pid);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_env	env;
	int		i;
	int		res;

	if ((argc != 5 && argc != 6) || ft_args(argc, argv, &env))
		return (1 + 0 * write(2, USAGE_MSG, 120));
	if (ft_before_after(&env, 0))
		return (2 + 0 * write(2, "Error on semaphores creating\n", 29));
	if (ft_processes(&env))
		return (3 + 0 * write(2, "Error on ft_processes creating\n", 31));
	i = -1;
	while (++i < env.n)
		sem_wait(env.all_eat_sem);
	res = 0;
	i = 0;
	while (i < env.n)
		if (kill(env.pid[i++], SIGINT) == -1)
			res = 4 + 0 * write(2, "Error on process killing\n", 25);
	i = 0;
	while (i < env.n)
		waitpid(env.pid[i++], NULL, 0);
	ft_before_after(&env, 1);
	return (res);
}
