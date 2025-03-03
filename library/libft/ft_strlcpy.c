/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:18:35 by naankour          #+#    #+#             */
/*   Updated: 2025/02/12 17:19:59 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy( char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i] != '\0')
		{
			i++;
		}
		return (i);
	}
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
/*
int main() {
    char dst[3] = "d";
    const char *src = "Coucouu";
    size_t copied_length;
    copied_length = ft_strlcpy(dst, src, 0);
    printf("Taille zéro:\n");
    printf("%s\n", src);
    printf("%s\n", dst);
    printf("%zu\n", copied_length);
    return 0;
}
*/
