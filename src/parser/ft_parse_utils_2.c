/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:28:44 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/24 10:07:03 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_add_object(t_counter *counter, char *type)
{
	if (ft_strcmp(type, "A") == 0)
		counter->ambient++;
	else if (ft_strcmp(type, "C") == 0)
		counter->camera++;
	else if (ft_strcmp(type, "L") == 0)
		counter->light++;
	else if (ft_strcmp(type, "sp") == 0)
		counter->sphere++;
	else if (ft_strcmp(type, "pl") == 0)
		counter->plane++;
	else if (ft_strcmp(type, "cy") == 0)
		counter->cylinder++;
}

int	ft_count_objects(t_counter *counter)
{
	if (counter->ambient != 1)
	{
		ft_print_error(ERROR_AMBIENT_BAD_COUNT, 0);
		return (1);
	}
	if (counter->camera != 1)
	{
		ft_print_error(ERROR_CAMERA_BAD_COUNT, 0);
		return (1);
	}
	if (counter->light < 1)
	{
		ft_print_error(ERROR_LIGHT_BAD_COUNT, 0);
		return (1);
	}
	return (0);
}

int	ft_check_coordinates(char *coords)
{
	char	**values;

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
