/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_p.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:39:24 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/23 11:41:15 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	count_len_ptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr > 0)
	{
		ptr = (ptr / 16);
		len++;
	}
	return (len);
}

static void	ft_putptr(uintptr_t ptr, int fd)
{
	if (ptr >= 16)
		ft_putptr(ptr / 16, fd);
	if (ptr % 16 <= 9)
		ft_putchar_fd(ptr % 16 + '0', fd);
	else
		ft_putchar_fd(ptr % 16 - 10 + 'a', fd);
}

int	ft_print_format_p(void *ptr)
{
	int	count;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		count = 5;
		return (count);
	}
	write(1, "0x", 2);
	count = count_len_ptr((uintptr_t)ptr) + 2;
	ft_putptr((uintptr_t)ptr, 1);
	return (count);
}
