/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:21:43 by naankour          #+#    #+#             */
/*   Updated: 2024/11/14 15:28:59 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	write (fd, s, i);
	write (fd, "\n", 1);
}

// int	main ()
// {
// 	char	s[] = "Bonjour";
// 	ft_putendl_fd(s, 1);
// 	return (0);
// }
