/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:26:58 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/20 14:56:12 by vimazuro         ###   ########.fr       */
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

static double	decimal_part(const char *nptr, size_t *i, int *err)
{
	double	result;
	double	divisor;

	result = 0;
	divisor = 10;
	if (nptr[*i] == '.')
	{
		(*i)++;
		if (!(nptr[*i] >= '0' && nptr[*i] <= '9'))
		{
			*err = 1;
			return (0);
		}
		while (nptr[*i] >= '0' && nptr[*i] <= '9')
		{
			result += (nptr[*i] - '0') / divisor;
			divisor *= 10;
			(*i)++;
		}
	}
	return (result);
}

double	ft_atof(const char *nptr, int *err)
{
	double	result;
	int		sign;
	size_t	i;
	
	*err = 0;
	if (!nptr || !*nptr)
	{
		*err = 1;
		return (0);
	}
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
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
	{
		*err = 1;
		return (0);
	}
	result = integer_part(nptr, &i);
	result += decimal_part(nptr, &i, err);
	if (*err)
		return (0);
	if (nptr[i] != '\0')
	{
		*err = 1;
		return (0);
	}
	return (sign * result);
}
