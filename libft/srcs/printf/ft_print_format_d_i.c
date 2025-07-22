/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_d_i.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:59:29 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/23 11:40:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	len = 0;
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n = (n / 10);
		len++;
	}
	return (len);
}

int	ft_print_format_d_i(int n)
{
	int	count;

	count = count_len(n);
	ft_putnbr_fd(n, 1);
	return (count);
}
