/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 18:45:40 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/27 13:03:27 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <pthread.h>
# include <sys/time.h>
# include "ft_types.h"

typedef struct s_fork	t_fork;

typedef struct s_g
{
	int				n_philos;
	t_bool			n_philos_is_even;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			n_times_to_eat;
	time_t			beginning;
	t_bool			someone_died;
	t_bool			simulation_should_stop;
	pthread_mutex_t	simulation_should_stop_mutex;
	int				c_well_fed_philos;
	pthread_mutex_t	sync_mutex;
	pthread_mutex_t	start_mutex;
	time_t			start_interval;
}	t_g;

typedef struct s_fork
{
	t_bool			is_free;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int			id;
	pthread_t	th;
	time_t		time_to_die;
	time_t		time_to_sleep;
	time_t		eating_timestamp;
	int			c_eating_times;
	time_t		timestamp;
	t_fork		*fork1;
	t_fork		*fork2;
	t_g			*g;
}	t_philo;

t_bool	read_args(t_g *g, int argc, char *argv[]);
t_bool	alloc(t_fork **p_forks, t_philo **p_philos, int n_philos);
t_bool	init(t_g *g, t_fork *forks, t_philo *philos);
t_bool	start(t_g *g, t_philo *philos);
t_bool	start_even(t_g *g, t_philo *philos);
t_bool	start_odd(t_g *g, t_philo *philos);
int		clean(t_g *g, t_fork *forks, t_philo *philos, int error);
void	*philo_run(void *arg);
t_bool	philo_must_stop(t_philo *philo);
time_t	now(void);
int		ft_sleep(t_g *g, time_t	milliseconds);

#endif
