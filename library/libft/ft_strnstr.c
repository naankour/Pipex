/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:58:56 by naankour          #+#    #+#             */
/*   Updated: 2024/11/09 12:33:27 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	if (len == 0)
		return (NULL);
	while (i < len && big[i] != '\0')
	{
		j = 0;
		while (big [i + j] == little[j] && little[j] && i + j <= len - 1)
		{
			j++;
		}
		if (little[j] == '\0' )
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
int	main()
{
	const char	big[] = "Hello World coucou";
	const char	little[] = "hello";
	size_t		len = 8;
	printf("resultat: %s", ft_strnstr(big, little, len));
	return (0);
}
*/
