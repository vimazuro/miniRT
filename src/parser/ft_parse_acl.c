/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_acl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:35:32 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 11:16:22 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_check_colors(t_color *colors)
{
	if (colors->r < 0 || colors->r > 255
		|| colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
	{
		ft_print_error(ERROR_AMBIENT_BAD_COLORS, 0);
		return (1);
	}
	return (0);
}

int	ft_parse_ambient(t_data *data, char **tokens)
{
	float	ratio;
	char	**colors;

	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		ft_print_error(ERROR_AMBIENT_BAD_PARAMS, 0);
		return (1);
	}
	ratio = ft_atof(tokens[1]);
	colors = ft_split(tokens[2], ',');
	if ((ratio < 0 || ratio > 1))
	{
		ft_free_split(colors);
		ft_print_error(ERROR_AMBIENT_BAD_RATIO, 0);
		return (1);
	}
	ft_free_split(colors);
	data->ambient.lighting = ratio;
	data->ambient.color = ft_parse_color(tokens[2]);
	if (ft_check_colors(&data->ambient.color))
		return (1);
	return (0);
}

int	ft_parse_camera(t_data *data, char **tokens)
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_CAMERA_BAD_PARAMS, 0);
		return (1);
	}
	position = ft_parse_vec3(tokens[1]);
	orientation = ft_parse_vec3(tokens[2]);
	fov = ft_atoi(tokens[3]);
	if (ft_check_position(position) || ft_check_coordinates(tokens[1]))
		return (1);
	if (ft_check_orientation(orientation) || ft_check_coordinates(tokens[2]))
		return (1);
	if (fov < 0 || fov > 180)
	{
		ft_print_error(ERROR_CAMERA_BAD_FOV, 0);
		return (1);
	}
	data->camera.position = position;
	data->camera.orientation = orientation;
	data->camera.fov = fov;
	return (0);
}

int	ft_parse_light(t_data *data, char **tokens)
{
	t_light	*light;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_LIGHT_BAD_PARAMS, 0);
		return (1);
	}
	light = malloc(sizeof(t_light));
	light->position = ft_parse_vec3(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	light->color = ft_parse_color(tokens[3]);
	light->next = data->lights;
	if (ft_check_position(light->position) || ft_check_coordinates(tokens[1]))
	{
		free(light);
		return (1);
	}
	if (light->brightness < 0 || light->brightness > 1)
	{
		ft_print_error(ERROR_LIGHT_BAD_BRIGHTNESS, 0);
		free(light);
		return (1);
	}
	data->lights = light;
	return (0);
}
