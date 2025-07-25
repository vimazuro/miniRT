/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_acl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:35:32 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 17:10:24 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_parse_ambient(t_data *data, char **tokens)
{
	data->ambient.lighting = ft_atof(tokens[1]);
	data->ambient.color = ft_parse_color(tokens[2]);
}

void	ft_parse_camera(t_data *data, char **tokens)
{
	data->camera.position = ft_parse_vec3(tokens[1]);
	data->camera.orientation = ft_parse_vec3(tokens[2]);
	data->camera.fov = ft_atoi(tokens[3]);
}

void	ft_parse_light(t_data *data, char **tokens)
{
	t_light	*light;
	t_light	*current;

	light = malloc(sizeof(t_light));
	light->position = ft_parse_vec3(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	light->color = ft_parse_color(tokens[3]);
	light->next = NULL;
	if (!data->lights)
		data->lights = light;
	else
	{
		current = data->lights;
		while (current->next)
			current = current->next;
		current->next = light;
	}
}
