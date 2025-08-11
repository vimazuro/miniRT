/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:47:45 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 15:40:44 by vimazuro         ###   ########.fr       */
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
	else if (ft_strcmp(type, "co") == 0)
		counter->cone++;
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
