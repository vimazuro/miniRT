/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloatpoint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:16:28 by vimazuro          #+#    #+#             */
/*   Updated: 2025/02/17 12:27:09 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isfloatpoint(const char *nptr)
{
	int	i;
	int	has_dot;
	int	has_digit;

	i = 0;
	has_dot = 0;
	has_digit = 0;
	if (!nptr || !nptr[0])
		return (0);
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i])
	{
		if (ft_isdigit(nptr[i]))
			has_digit = 1;
		else if (nptr[i] == '.' && !has_dot)
			has_dot = 1;
		else
			return (0);
		i++;
	}
	return (has_digit);
}
