/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:29:31 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 16:46:33 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

# define ERROR "\e[31mError:\e[0m"
# define INT_LEN 10
# define ARG5 6

enum e_forks {
	unlock,
	lock
};

enum e_status {
	eating,
	sleeping
};

typedef struct s_philo {
	int				id;
	int				*value;
	int				*arg5;
	long			ut0;
	long			ut1;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
}	t_philo;

int		*ft_parser(const int argc, char **argv);
int		ft_init(int argc, int *value);
int		ft_free(int *value, pthread_mutex_t *forkMutex, t_philo *philo);

long	ft_get_time(void);

void	*ft_philo(void *tid);
void	*ft_watcher(void *tid);
void	ft_usleep(long time, t_philo *philo);

#endif
