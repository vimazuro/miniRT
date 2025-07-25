/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_x.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:51:54 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/23 11:42:38 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_len_x(unsigned int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		n = (n / 16);
		len++;
	}
	return (len);
}

static void	ft_putnbr_fd_x(unsigned int n, int fd, const char format)
{
	if (n >= 16)
		ft_putnbr_fd_x(n / 16, fd, format);
	if (n % 16 <= 9)
		ft_putchar_fd(n % 16 + '0', fd);
	else
	{
		if (format == 'x')
			ft_putchar_fd(n % 16 - 10 + 'a', fd);
		else if (format == 'X')
			ft_putchar_fd(n % 16 - 10 + 'A', fd);
	}
}

int	ft_print_format_x(unsigned int n, const char format)
{
	int	count;

	count = count_len_x(n);
	ft_putnbr_fd_x(n, 1, format);
	return (count);
}
