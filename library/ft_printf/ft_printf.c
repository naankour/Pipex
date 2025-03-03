/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:16:01 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 11:51:26 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_ap(int i, int count, const char *format, va_list ap)
{
	if (format[i] == 'c')
		count += ft_print_c((char)va_arg(ap, int));
	else if (format[i] == 'd' || format [i] == 'i')
		count += ft_print_d_i(va_arg(ap, int));
	else if (format[i] == 's')
		count += ft_print_s(va_arg(ap, char *));
	else if (format[i] == 'p')
		count += ft_print_p(va_arg(ap, unsigned long));
	else if (format[i] == 'u')
		count += ft_print_u(va_arg(ap, unsigned int));
	else if (format[i] == '%')
		count += ft_print_c('%');
	else if (format[i] == 'x')
		count += ft_print_x(va_arg(ap, unsigned int), 0);
	else if (format[i] == 'X')
		count += ft_print_x(va_arg(ap, unsigned int), 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		i;

	va_start(ap, format);
	count = 0;
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] != '%')
		{
			ft_print_c(format[i]);
			count++;
		}
		else
		{
			i++;
			count = ft_printf_ap(i, count, format, ap);
		}
		i++;
	}
	va_end(ap);
	return (count);
}
