/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:05:58 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/22 12:55:56 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format(va_list args, const char format)
{
	size_t	count;

	count = 0;
	if (format == 'c')
		count += ft_print_format_c(va_arg(args, int));
	else if (format == 's')
		count += ft_print_format_s(va_arg(args, char *));
	else if (format == 'p')
		count += ft_print_format_p(va_arg(args, void *));
	else if ((format == 'd') || (format == 'i'))
		count += ft_print_format_d_i(va_arg(args, int));
	else if (format == 'u')
		count += ft_print_format_u(va_arg(args, unsigned int));
	else if ((format == 'x') || (format == 'X'))
		count += ft_print_format_x(va_arg(args, unsigned int), format);
	else if (format == '%')
		count += ft_print_format_percent();
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		res;

	i = 0;
	res = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			res += ft_format(args, str[i + 1]);
			i += 2;
		}
		else
		{
			write(1, &str[i], 1);
			i++;
			res++;
		}
	}
	va_end(args);
	return (res);
}
