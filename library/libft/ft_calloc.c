/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 07:27:43 by naankour          #+#    #+#             */
/*   Updated: 2024/11/20 13:46:44 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*arr;
	size_t			i;

	if (nmemb != 0 && nmemb * size / nmemb != size)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}

// int	main()
// {
// 	size_t	nmemb = 5;
// 	size_t	size = sizeof(int);
// 	int	*arr = ft_calloc(nmemb, size);

// 	size_t  i = 0;
// 	while (i < nmemb)
// 	{
// 		printf("%d", arr[i]);
// 		i++;
// 	}
// 	return (0);
// }
