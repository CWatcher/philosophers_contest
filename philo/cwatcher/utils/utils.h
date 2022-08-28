/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: CWatcher <cwatcher@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:32:57 by CWatcher          #+#    #+#             */
/*   Updated: 2021/08/15 11:11:37 by CWatcher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include <sys/types.h>

ssize_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
int				ft_atoi(char *str);
int				ft_isdigit(int c);
char			*ft_skipchrs(const char *s, const char *delim);
void			ft_putstr_fd(const char *s, int fd);
long			min(long x, long y);
#endif
