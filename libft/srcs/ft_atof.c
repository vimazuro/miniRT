/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:26:58 by vimazuro          #+#    #+#             */
/*   Updated: 2025/02/17 13:16:22 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	integer_part(const char *nptr, size_t *i)
{
	double	result;

	result = 0;
	while (nptr[*i] >= '0' && nptr[*i] <= '9')
	{
		result = (result * 10) + (nptr[*i] - '0');
		(*i)++;
	}
	return (result);
}

static double	decimal_part(const char *nptr, size_t *i)
{
	double	result;
	double	divisor;

	result = 0;
	divisor = 10;
	if (nptr[*i] == '.')
	{
		(*i)++;
		while (nptr[*i] >= '0' && nptr[*i] <= '9')
		{
			result += (nptr[*i] - '0') / divisor;
			divisor *= 10;
			(*i)++;
		}
	}
	return (result);
}

double	ft_atof(const char *nptr)
{
	double	result;
	int		sign;
	size_t	i;

	if (!nptr || !*nptr)
		return (0);
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = integer_part(nptr, &i);
	result += decimal_part(nptr, &i);
	return (sign * result);
}
