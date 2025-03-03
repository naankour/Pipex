/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:49:24 by naankour          #+#    #+#             */
/*   Updated: 2024/11/09 12:30:37 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
		{
			return ((void *)(s + i));
		}
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	const char	s[] = "Hello";
	unsigned char 	c = 'e';
	size_t		n = 5;

	ft_memchr(s,c,n);

	printf("%c",c);
	return (0);
}
*/
