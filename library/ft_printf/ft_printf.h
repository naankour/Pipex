/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naankour <naankour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:57:09 by naankour          #+#    #+#             */
/*   Updated: 2024/11/25 13:00:54 by naankour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int	ft_print_c(char c);
int	ft_print_s(char	*str);
int	ft_print_d_i(int nb);
int	ft_print_u(unsigned long nb);
int	ft_print_x(unsigned long nb, int upper);
int	ft_print_p(unsigned long nb);
int	ft_printf(const char *format, ...);

#endif
