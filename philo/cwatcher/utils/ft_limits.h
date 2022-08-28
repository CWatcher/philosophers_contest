/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_limits.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:06:03 by CWatcher          #+#    #+#             */
/*   Updated: 2021/08/12 15:16:54 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIMITS_H
# define FT_LIMITS_H

# define INT_MAX ((int)0x7FFFFFFF)
# define INT_MIN ((int)0x80000000)
# define LONG_MAX ((long)0x8000000000000000)
# ifndef _STDINT_H_
#  define UINT32_MAX ((unsigned)-1)
# endif
#endif
