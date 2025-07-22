/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:58:17 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:30:05 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_free_lights(t_light *light)
{
	t_light	*tmp;

	while (light)
	{
		tmp = light->next;
		free(light);
		light = tmp;
	}
}

static void	ft_free_objects(t_object *obj)
{
	t_object	*tmp;

	while (obj)
	{
		tmp = obj->next;
		if (obj->data)
		{
			if (obj->type == SPHERE)
				free((t_sphere *)obj->data);
			else if (obj->type == PLANE)
				free((t_plane *)obj->data);
		}
		free(obj);
		obj = tmp;
	}
}

void	ft_free_data(t_data *data)
{
	if (!data)
		return ;
	ft_free_lights(data->lights);
	data->lights = NULL;
	ft_free_objects(data->objects);
	data->objects = NULL;
}
