/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:35:29 by kannie            #+#    #+#             */
/*   Updated: 2022/06/24 16:35:45 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/types.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

typedef struct s_philo
{
	int				id;
	pid_t			pid_id;
	int				nbr_philo;
	long long		start;
	int				must_eat;
	long long		last_eat;
	long long		time_to_life;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nbr_eat;
	int				sigone_p;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*kill;
	pthread_t		check_life;
}	t_philo;

typedef struct s_waiter
{
	sem_t			*forks;
	sem_t			*print;
	sem_t			*kill;
	t_philo			*philo;
	long long		start;
	int				must_eat;
	int				nbr_philo;
	long long		time_to_life;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				sigone_p;
}	t_waiter;

int			ft_atoi(const char *str);
int			schar_v_int(const char *strok, int i, int minus);
int			check_str(char *str);
int			print_exit(int i);
int			values_waiter(char *str[], t_waiter *waiter);
void		values_philo(t_waiter *waiter, t_philo *philo, int i);
void		init_sem(t_waiter *waiter);
int			num_portion(char *str, t_waiter *waiter);
void		philo_create(t_waiter *waiter);
void		philo_life(t_philo *buf);
void		what_philo_do(t_philo *philo, char *str,
				long long time_to_do);
void		ft_sleep_philo(long long time_do);
long long	time_to(void);
void		*philo_check(void *buf);
void		check_ate(t_waiter *waiter);
void		take_forks(t_philo *philo);

#endif