/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d_i.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:44:37 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 11:41:13 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long	ft_nlen(long n)
{
	long	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len ++;
		n = n * (-1);
	}
	while (n > 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static void	*ft_mem(long len)
{
	char	*str;

	str = (char *) malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	return (str);
}

static char	*ft_itoa(int n)
{
	long	len;
	char	*str;
	long	num;

	num = n;
	len = ft_nlen(n);
	str = ft_mem(len);
	str[len] = '\0';
	if (num == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (num < 0)
	{
		str[0] = '-';
		num = num * (-1);
	}
	while (num > 0)
	{
		str[--len] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

int	ft_print_d_i(int nb)
{
	char	*str;
	int		i;

	str = ft_itoa(nb);
	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		ft_print_c(str[i]);
		i++;
	}
	free (str);
	return (i);
}
// int	main()
// {
// 	int	nb = -2147483648;
// 	printf("%ld\n", -2147483648);
// 	ft_print_d_i(nb);
// 	return (0);
// }
