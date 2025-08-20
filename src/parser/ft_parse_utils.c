/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:28:55 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/20 14:24:12 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_check_position(t_vec3 position, const char *obj_name)
{
	if (position.x < -50 || position.x > 50
		|| position.y < -50 || position.y > 50
		|| position.z < -50 || position.z > 50)
	{
		if (ft_strcmp(obj_name, "camera") == 0)
			ft_print_error(ERROR_CAMERA_BAD_POSITION, 0);
		else if (ft_strcmp(obj_name, "light") == 0)
			ft_print_error(ERROR_LIGHT_BAD_POSITION, 0);
		else if (ft_strcmp(obj_name, "plane") == 0)
			ft_print_error(ERROR_PLANE_BAD_POSITION, 0);
		else if (ft_strcmp(obj_name, "sphere") == 0)
			ft_print_error(ERROR_SPHERE_BAD_POSITION, 0);
		else if (ft_strcmp(obj_name, "cylinder") == 0)
			ft_print_error(ERROR_CYLINDER_BAD_POSITION, 0);
		else if (ft_strcmp(obj_name, "cone") == 0)
			ft_print_error(ERROR_CONE_BAD_POSITION, 0);
		return (1);
	}
	return (0);
}

int	ft_check_orientation(t_vec3 orientation, const char *obj_name)
{
	if (orientation.x < -1 || orientation.x > 1
		|| orientation.y < -1 || orientation.y > 1
		|| orientation.z < -1 || orientation.z > 1
		|| (orientation.x == 0 && orientation.y == 0 && orientation.z == 0))
	{
		if (ft_strcmp(obj_name, "camera") == 0)
			ft_print_error(ERROR_CAMERA_BAD_ORIENTATION, 0);
		else if (ft_strcmp(obj_name, "plane") == 0)
			ft_print_error(ERROR_PLANE_BAD_ORIENTATION, 0);
		else if (ft_strcmp(obj_name, "cylinder") == 0)
			ft_print_error(ERROR_CYLINDER_BAD_ORIENTATION, 0);
		else if (ft_strcmp(obj_name, "cone") == 0)
			ft_print_error(ERROR_CONE_BAD_ORIENTATION, 0);
		return (1);
	}
	return (0);
}

t_color	ft_parse_color(char *str)
{
	char	**rgb;
	t_color	color;

	color.r = -1;
	color.g = -1;
	color.b = -1;
	rgb = ft_split(str, ',');
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free_split(rgb);
		return (color);
	}
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	color.pixel_color = (color.r << 24) | (color.g << 16)
		| (color.b << 8) | 255;
	ft_free_split(rgb);
	return (color);
}

t_vec3	ft_parse_vec3(char *str, int *err)
{
	char	**xyz;
	t_vec3	vec3;
	int		local_err;

	*err = 0;
	xyz = ft_split(str, ',');
	if (!xyz[0] || !xyz[1] || !xyz[2] || xyz[3])
	{
		ft_free_split(xyz);
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		*err = 1;
		return ((t_vec3){0, 0, 0});
	}
	vec3.x = ft_atof(xyz[0], &local_err);
	if (local_err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		ft_free_split(xyz);
		*err = 1;
		return ((t_vec3){0, 0, 0});
	}
		
	vec3.y = ft_atof(xyz[1], &local_err);
	if (local_err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		ft_free_split(xyz);
		*err = 1;
		return ((t_vec3){0, 0, 0});
	}
	vec3.z = ft_atof(xyz[2], &local_err);
	if (local_err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		ft_free_split(xyz);
		*err = 1;
		return ((t_vec3){0, 0, 0});
	}
	ft_free_split(xyz);
	return (vec3);
}

void	ft_free_split(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
