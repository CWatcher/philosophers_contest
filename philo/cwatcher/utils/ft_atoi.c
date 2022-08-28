/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 20:07:37 by cwatcher          #+#    #+#             */
/*   Updated: 2021/07/29 16:52:44 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "ft_types.h"
#include "ft_limits.h"

int	ft_atoi(char *s)
{
	unsigned int	n;
	unsigned int	prev_n;
	t_bool			minus;

	s = ft_skipchrs(s, " \t\n\r\f\v");
	minus = false;
	if (*s == '-')
		minus = true;
	s += (*s == '-' || *s == '+');
	s = ft_skipchrs(s, "0");
	n = 0;
	while (ft_isdigit(*s) && n < INT_MAX)
	{
		prev_n = n;
		n = n * 10 + (*s - '0');
		++s;
		if (n <= prev_n || n > INT_MAX)
			n = INT_MAX + (unsigned)minus;
	}
	while (ft_isdigit(*s))
		++s;
	if (minus)
		return (-n);
	return (n);
}
