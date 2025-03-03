/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:49:34 by naankour          #+#    #+#             */
/*   Updated: 2025/02/12 17:54:00 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
// size_t	ft_strlen(const char *str);
int		ft_strchr_2(const char *s, int c);
char	*ft_strjoin_2(char *s1, char *s2);
char	*ft_strdup_2(char *src);
char	*ft_update_buffer(char *buffer);
char	*ft_read(int fd, char *buffer, char *temp);

#endif
