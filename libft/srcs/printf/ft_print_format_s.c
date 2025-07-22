/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_format_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:57:05 by vimazuro          #+#    #+#             */
/*   Updated: 2024/10/23 11:41:56 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_format_s(char *s)
{
	int	count;

	if (!s)
	{
		write(1, "(null)", 6);
		count = 6;
		return (count);
	}
	count = ft_strlen(s);
	ft_putstr_fd(s, 1);
	return (count);
}
