/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:34:50 by naankour          #+#    #+#             */
/*   Updated: 2024/11/14 14:37:09 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

// void	ft_example(unsigned int i, char *c)
// {
// 	 printf("Index %u: %s\n", i, c);
// }
// int	main()
// {
// 	char s[] = "Hello";
// 	ft_striteri(s, &ft_example);
// 	return (0);
// }
