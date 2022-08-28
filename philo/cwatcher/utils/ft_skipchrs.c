/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipchrs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:36:06 by CWatcher          #+#    #+#             */
/*   Updated: 2021/07/29 16:53:22 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_skipchrs(const char *s, const char *delim)
{
	while (s && *s && ft_strchr(delim, *s))
		s++;
	return ((char *)s);
}
