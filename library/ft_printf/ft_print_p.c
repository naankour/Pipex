/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:06:12 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 13:10:34 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_p(unsigned long nb)
{
	int	len;

	if (!nb)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	len = ft_print_x(nb, 0);
	return (len + 2);
}

/*
int	main ()
{
	int	x = 515645;
	int	*p = &x;
	int	len = ft_print_p(unsigned long);
	printf("%d\n", len);
	return (0);
}

int	main()
{
	int	a = 10;
	printf("adresse de a: %p\n", a);
	return (0);
}
*/
