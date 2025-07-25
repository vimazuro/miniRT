/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:05:28 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/23 11:42:17 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_len_u(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = (n / 10);
		len++;
	}
	return (len);
}

static void	ft_putnbr_fd_u(unsigned int n, int fd)
{
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10) + '0', fd);
}

int	ft_print_format_u(unsigned int n)
{
	int	count;

	count = count_len_u(n);
	ft_putnbr_fd_u(n, 1);
	return (count);
}
