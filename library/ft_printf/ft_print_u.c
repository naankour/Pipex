/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 08:29:39 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 13:01:32 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_unsigned(unsigned long nb)
{
	if (nb >= 10)
	{
		ft_putnbr_unsigned(nb / 10);
	}
	ft_print_c((nb % 10) + 48);
}

int	ft_print_u(unsigned long nb)
{
	int	count;

	ft_putnbr_unsigned(nb);
	count = 0;
	if (nb == 0)
	{
		return (1);
	}
	while (nb > 0)
	{
		nb = nb / 10;
		count ++;
	}
	return (count);
}

// int	ft_print_u(unsigned int nb)
// {
// 	int	count;

// 	count = 0;

// 	if (nb <= 9)
// 	{
// 		ft_print_c(nb + 48);
// 		return (1);
// 	}
// 	count = count + ft_print_u(nb / 10);
// 	ft_print_c((nb % 10) + 48);
// 	return (count + 1);
// }

// int	main()
// {
// 	unsigned int	nb = 52;
// 	printf("%u\n", nb);
// 	ft_print_u(nb);
// 	return (0);
// }
