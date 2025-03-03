/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 09:09:51 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 13:10:15 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_s(char	*str)
{
	int	i;

	if (!str)
	{
		str = "(null)";
	}
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

// int	main()
// {
// 	char	str[] = "Coucou";
// 	printf("%s\n", str);
// 	ft_print_s(str);
// 	return (0);
// }

// int	ft_print_c(char c)
// {
// 	write(1, &c, 1);
// 	return (1);
// }
