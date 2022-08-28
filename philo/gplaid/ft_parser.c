/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvenmo <mvenmo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:36:39 by mvenmo            #+#    #+#             */
/*   Updated: 2022/08/09 17:37:32 by mvenmo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	if (*str == '\0')
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\v' || \
			*str == '\r' || *str == '\n' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*(str++) == '-')
			sign = -1;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (((result * sign) >= (-2147483648)) && (result * sign <= 2147483647))
		return (sign * result);
	else if (sign > 0)
		return (-1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

static int	*parser_value(const int argc, char **argv)
{
	int	*value;
	int	j;
	int	i;

	j = 0;
	i = 1;
	value = (int *)malloc(sizeof(int) * (argc - 1));
	if (!value)
		return (NULL);
	while (i && argv[i])
	{
		value[j] = ft_atoi(argv[i++]);
		if (value[j++] <= 0)
			i ^= i;
	}
	if (i)
		return (value);
	printf(ERROR " arg%d - \"%s\"\n", j, argv[j]);
	free(value);
	value = NULL;
	return (value);
}

int	*ft_parser(const int argc, char **argv)
{
	int	flag;
	int	j;
	int	i;

	flag = 1;
	j = 0;
	i = 1;
	while (flag && argv[j++])
	{
		i ^= i;
		if (i)
			break ;
		while (flag && argv[j] && argv[j][i])
			if (! ft_isdigit(argv[j][i++]) || i > INT_LEN)
				flag ^= flag;
	}
	if (flag)
		return (parser_value(argc, argv));
	printf(ERROR " arg%d - \"%s\"\n", j, argv[j]);
	return (NULL);
}
