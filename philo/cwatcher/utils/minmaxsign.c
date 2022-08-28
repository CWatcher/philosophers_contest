/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmaxsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.r>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 01:23:43 by CWatcher          #+#    #+#             */
/*   Updated: 2022/01/27 16:37:03 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	min(long x, long y)
{
	if (x < y)
		return (x);
	return (y);
}

long	max(long x, long y)
{
	if (x > y)
		return (x);
	return (y);
}

long	sign(long x)
{
	if (x >= 0)
		return (1);
	return (-1);
}
