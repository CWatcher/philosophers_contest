/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:30:54 by mvenmo            #+#    #+#             */
/*   Updated: 2022/03/06 16:11:36 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <errno.h>

# define USAGE_MSG "Usage: ./philo_bonus number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

typedef struct s_env {
	pid_t		*pid;
	pthread_t	th;
	int			id;
	long		die_at;
	int			n;
	sem_t		*eat_sem;
	sem_t		*print_sem;
	sem_t		*forks;
	sem_t		*garcon_sem;
	sem_t		*all_eat_sem;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			n_times_to_eat;
	long		start_time;
}	t_env;

long	current_time(void);
int		ft_processes(t_env *env);
int		ft_before_after(t_env *env, int mode);

#endif
