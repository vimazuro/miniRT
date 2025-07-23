/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:55:25 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/23 15:56:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_count_objects(t_counter *counter, char *type)
{
	if (ft_strcmp(type, "A") == 0)
	{
		counter->ambient++;
		if (counter->ambient > 1)
			ft_print_error(ERROR_OBJECTS_EXCESS_AMBIENT, 0);
		return (counter->ambient - 1);
	}
	else if (ft_strcmp(type, "C") == 0)
	{
		counter->camera++;
		if (counter->camera > 1)
			ft_print_error(ERROR_OBJECTS_EXCESS_CAMERA, 0);
		return (counter->camera - 1);
	}
	else if (ft_strcmp(type, "L") == 0)
	{
		counter->light++;
		if (counter->light > 10)
			ft_print_error(ERROR_OBJECTS_EXCESS_LIGHT, 0);
		return (counter->light - 1);
	}
	return (0);
}