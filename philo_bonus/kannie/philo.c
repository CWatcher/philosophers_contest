/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:30:18 by kannie            #+#    #+#             */
/*   Updated: 2022/06/23 19:34:31 by kannie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_exit(int i)
{
	if (i == -1)
		printf("\033[0;31mError\e[0m\n");
	return (i);
}

int	main(int argc, char **argv)
{
	t_waiter	waiter;
	int			info;

    waiter = (t_waiter){0};
	info = 0;
	if (argc >= 5 && argc <= 6)
	{
		info = values_waiter(argv, &waiter);
		if (info < 0)
			return (print_exit(info));
		philo_create(&waiter);
		free (waiter.philo);
		sem_unlink("sem_forks");
		sem_unlink("sem_print");
		sem_close(waiter.forks);
		sem_close(waiter.print);
		return (print_exit(info));
	}
	else
		return (print_exit(1));
}
