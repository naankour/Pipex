/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:32:17 by naankour          #+#    #+#             */
/*   Updated: 2024/11/09 11:55:12 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (((c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z'))
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int	main()
{
	int	c = 'A';
	int	result = ft_isalnum(c);

	printf("%d", result);
	return (0);
}
*/
