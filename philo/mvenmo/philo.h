/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 09:30:54 by mvenmo            #+#    #+#             */
/*   Updated: 2022/03/01 14:33:27 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define USAGE_MSG "Usage: ./philo number_of_philosophers \
time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n"

struct	s_env;

typedef struct s_phil {
	pthread_t		th;
	pthread_mutex_t	eat_mutex;
	int				id;
	struct s_env	*env_address;
	int				times_to_eat;
	long			die_at;
}	t_phil;

typedef struct s_env {
	t_phil			*ph;
	pthread_mutex_t	*forks;
	volatile int	stop;
	pthread_mutex_t	print_mutex;
	int				n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat;
	long			start_time;
}	t_env;

void	*philosopher(void *arg);
long	current_time(void);

#endif