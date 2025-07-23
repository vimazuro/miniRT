/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:51:42 by vimazuro          #+#    #+#             */
/*   Updated: 2024/11/25 12:06:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>
# include "libft.h"

int	ft_printf(char const *str, ...);
int	ft_format(va_list args, const char format);
int	ft_print_format_c(char c);
int	ft_print_format_s(char *s);
int	ft_print_format_p(void *ptr);
int	ft_print_format_d_i(int n);
int	ft_print_format_u(unsigned int n);
int	ft_print_format_x(unsigned int n, const char format);
int	ft_print_format_percent(void);

#endif
