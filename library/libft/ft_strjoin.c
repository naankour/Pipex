/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:19:17 by naankour          #+#    #+#             */
/*   Updated: 2024/11/12 10:38:16 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	new = malloc(s1_len + s2_len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < s1_len && s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < s2_len && s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[s1_len + s2_len] = '\0';
	return (new);
}
/*
int	main ()
{
	const char	s1[] = "Bonjour";
	const char	s2[] = " Coucou";
	char		*result = ft_strjoin(s1, s2);

	printf ("%s", result);
	return (0);
}
*/
