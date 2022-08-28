/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:35:29 by kannie            #+#    #+#             */
/*   Updated: 2022/05/24 14:46:36 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				nbr_philo;
	long long		start;
	pthread_t		life_philo;
	long long		last_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				f_kill;
	int				nbr_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutx;
}	t_philo;

typedef struct s_waiter
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutx;
	t_philo			*philo;
	long long		start;
	int				s_die;
	int				sig_eat;
	int				must_eat;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}	t_waiter;

int			ft_atoi(const char *str);
int			schar_v_int(const char *strok, int i, int minus);
int			check_str(char *str);
int			create_philo(t_waiter *waiter);
int			init_mut(t_waiter *waiter);
void		*philo_life(void *buf);
int			values_waiter(char *str[], t_waiter *waiter);
int			num_portion(char *str, t_waiter *waiter);
void		values_philo(t_waiter *waiter, t_philo *philo, int i);
long long	time_to(void);
void		what_philo_do(t_philo *philo, char *str,
				int time_to_do);
void		lock_fork(t_philo *philo);
void		unlock_fork(t_philo *philo);
int			print_exit(int i);
void		ft_sleep_philo(long long time_do, t_philo *philo);
void		f_life(t_philo *philo);
void		waiter_check(t_waiter *waiter);
void		waiter_philo(t_waiter *waiter);
int			philo_check_dide(t_philo *philo);
void		check_1_philo(t_philo *philo);

#endif