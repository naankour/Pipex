/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:38:04 by naankour          #+#    #+#             */
/*   Updated: 2024/11/14 15:30:18 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*new;
	size_t	i;

	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new[i] = (*f)(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
// char	ft_example(unsigned int i, char c)
// {
// 	return (c + i);
// }
// int	main()
// {
// 	const char	s[] = "Bonjour";
// 	char	*result = ft_strmapi(s, ft_example);

// 	printf("Chaîne modifiée : %s\n", result);
// 	return 0;
// }
