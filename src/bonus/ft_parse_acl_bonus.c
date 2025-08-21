/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_acl_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:35:32 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/20 16:52:42 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_check_colors(t_color *colors, const char *obj_name)
{
	if (colors->r < 0 || colors->r > 255
		|| colors->g < 0 || colors->g > 255
		|| colors->b < 0 || colors->b > 255)
	{
		if (ft_strcmp(obj_name, "ambient") == 0)
			ft_print_error(ERROR_AMBIENT_BAD_COLORS, 0);
		else if (ft_strcmp(obj_name, "light") == 0)
			ft_print_error(ERROR_LIGHT_BAD_COLORS, 0);
		else if (ft_strcmp(obj_name, "sphere") == 0)
			ft_print_error(ERROR_SPHERE_BAD_COLORS, 0);
		else if (ft_strcmp(obj_name, "plane") == 0)
			ft_print_error(ERROR_PLANE_BAD_COLORS, 0);
		else if (ft_strcmp(obj_name, "cylinder") == 0)
			ft_print_error(ERROR_CYLINDER_BAD_COLORS, 0);
		else if (ft_strcmp(obj_name, "cone") == 0)
			ft_print_error(ERROR_CONE_BAD_COLORS, 0);
		return (1);
	}
	return (0);
}

int	ft_parse_ambient(t_data *data, char **tokens)
{
	float	ratio;
	char	**colors;
	int		err;

	if (!tokens[0] || !tokens[1] || !tokens[2] || tokens[3])
	{
		ft_print_error(ERROR_AMBIENT_BAD_PARAMS, 0);
		return (1);
	}
	ratio = ft_atof(tokens[1], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		return (1);
	}
	colors = ft_split(tokens[2], ',');
	if ((ratio < 0.1 || ratio > 1))
	{
		ft_free_split(colors);
		ft_print_error(ERROR_AMBIENT_BAD_RATIO, 0);
		return (1);
	}
	ft_free_split(colors);
	data->ambient.lighting = ratio;
	data->ambient.color = ft_parse_color(tokens[2]);
	if (ft_check_colors(&data->ambient.color, "ambient"))
		return (1);
	return (0);
}

int	ft_parse_camera(t_data *data, char **tokens)
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
	int		err;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_CAMERA_BAD_PARAMS, 0);
		return (1);
	}
	if (ft_check_coordinates(tokens[1]) || ft_check_coordinates(tokens[2]))
		return (1);
	position = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (1);
	orientation = ft_parse_vec3(tokens[2], &err);
	if (err)
		return (1);
	fov = ft_atoi(tokens[3]);
	if (ft_check_position(position, "camera"))
		return (1);
	if (ft_check_orientation(orientation, "camera"))
		return (1);
	if (fov < 0 || fov > 180)
	{
		ft_print_error(ERROR_CAMERA_BAD_FOV, 0);
		return (1);
	}
	data->camera.position = position;
	data->camera.orientation = vec3_normalize(orientation);
	data->camera.fov = fov;
	return (0);
}

int	ft_parse_light(t_data *data, char **tokens)
{
	t_light	*light;
	int		err;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_LIGHT_BAD_PARAMS, 0);
		return (1);
	}
	if (ft_check_coordinates(tokens[1]))
		return (1);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		ft_print_error(ERROR_MALLOC, 0);
		return (1);
	}
	light->position = ft_parse_vec3(tokens[1], &err);
	if (err)
	{
		free(light);
		return (1);
	}
	light->brightness = ft_atof(tokens[2], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(light);
		return (1);
	}
	light->color = ft_parse_color(tokens[3]);
	light->next = data->lights;
	if (ft_check_position(light->position, "light"))
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
	if (ft_check_colors(&light->color, "light"))
		return (1);
	data->lights = light;
	return (0);
}
