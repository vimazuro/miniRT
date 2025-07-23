/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:28:44 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/23 16:36:17 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int ft_check_coordinate_amount(char *coords)
{
	char **values;

	values = ft_split(coords, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		ft_free_split(values);
		ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
		return (1);
	}
	ft_free_split(values);
	return (0);
}