/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epandele <epandele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 14:26:01 by epandele          #+#    #+#             */
/*   Updated: 2026/09/11 18:00:15 by epandele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

<<<<<<< HEAD:GNL/get_next_line.h
int		ft_strlen(const char *s);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
char		*get_next_line(int fd);
=======
int		gnl_ft_strlen(const char *s);
char	*gnl_ft_strjoin(char *s1, char *s2);
char	*gnl_ft_strchr(const char *s, char c);
char	*gnl_ft_strdup(const char *src);

char	*get_next_line(int fd);
>>>>>>> elvis:srcs/GNL/get_next_line.h

#endif