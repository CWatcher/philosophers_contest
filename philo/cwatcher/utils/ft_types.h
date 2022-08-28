/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 19:05:42 by CWatcher          #+#    #+#             */
/*   Updated: 2021/07/30 19:05:45 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPES_H
# define FT_TYPES_H
/*
** <stdbool.h>
*/
typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;
/*
** <stdint.h>
*/
typedef unsigned long	t_uint64;
typedef unsigned		t_uint32;
typedef unsigned short	t_uint16;
typedef unsigned char	t_uint8;
typedef unsigned		t_int32;
#endif
