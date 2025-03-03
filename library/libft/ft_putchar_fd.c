/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:45:34 by naankour          #+#    #+#             */
/*   Updated: 2024/11/14 15:04:47 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// #include <fcntl.h>

// int	main()
// {
// 	int fd = open("file", O_RDONLY);
// 	printf("file fd = %d\n", fd);
// 	if (fd == -1)
// 		printf("Error\n");
// 	char	c = 'A';
// 	ft_putchar_fd(c, fd);
// }
