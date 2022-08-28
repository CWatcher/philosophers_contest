/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:42:39 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 16:43:20 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	err_arg(char *str)
{
	printf(ERROR " %s\n", str);
	return (1);
}

int	main(int argc, char **argv)
{
	int	*value;

	if (argc < 5 || argc > 6)
		return (err_arg("argc"));
	value = ft_parser(argc, argv);
	if (!value)
		return (1);
	else if (!ft_init(argc, value))
		return (1);
	return (0);
}
