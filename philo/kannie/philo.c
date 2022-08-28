/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kannie <kannie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 16:30:18 by kannie            #+#    #+#             */
/*   Updated: 2022/08/19 11:59:51 by kannie           ###   ########.fr       */
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
		info = create_philo(&waiter);
		if (info < 0)
		{
			free(waiter.forks);
			return (print_exit(info));
		}
		free (waiter.philo);
		free (waiter.forks);
		return (print_exit(info));
	}
	else
		return (print_exit(1));
}
