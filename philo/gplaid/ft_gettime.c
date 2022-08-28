/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gettime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:32:08 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 16:47:13 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <sys/time.h>

long	ft_get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec * 1e-3);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	i;

	i = ft_get_time() + time;
	while (i > ft_get_time() && philo->value[1])
		usleep(500);
}

int	ft_free(int *value, pthread_mutex_t *forkMutex, t_philo *philo)
{
	free(value);
	if (forkMutex)
		free(forkMutex);
	if (philo)
		free(philo);
	return (0);
}
