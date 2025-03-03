/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:57:44 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 12:55:42 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_x(unsigned long nb, int upper)
{
	int		count;
	char	*hexadecimal_base;

	if (upper)
		hexadecimal_base = "0123456789ABCDEF";
	else
		hexadecimal_base = "0123456789abcdef";
	count = 0;
	if (nb == 0)
	{
		ft_print_c('0');
		return (1);
	}
	if (nb >= 16)
	{
		count = count + ft_print_x((nb / 16), upper);
	}
	ft_print_c(hexadecimal_base[nb % 16]);
	count ++;
	return (count);
}
// int main(void)
// {
// 	int nb = 0;
// 	int len = ft_print_x_X(nb, 1);
// 	write(1, "\n", 1);

// 	printf("%d\n", len);
// 	ft_print_x_X(nb, 1);
// 	return (0);
// }
// int	main()
// {
// 	int	i;
// 	i = 0x7FEA;
// 	printf("%x\n", i);
// 	return (0);
// }

// void	ft_putnbr_hex(int nb, int upper)
// {
// 	char	*hexadecimal_base;

// 	if (upper)
// 		hexadecimal_base = "0123456789ABCDEF";
// 	else
// 		hexadecimal_base = "0123456789abcdef";

// 	if (nb >= 16)
// 	{
// 		ft_putnbr_hex((nb / 16), upper);
// 	}
// 	ft_print_c(hexadecimal_base[nb % 16]);
// }
// if (nb == 0)
// 	{
// 		ft_print_c('0');
// 		return (1);
	// }
	// ft_putnbr_hex(nb, upper);

	// count = 0;
	// while (nb > 0)
	// {
	// 	nb = nb / 16;
	// 	count ++;
	// }
	// return (count);
