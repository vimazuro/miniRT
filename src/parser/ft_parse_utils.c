/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:28:55 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 16:33:07 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_check_position(t_vec3 position)
{
	if (position.x < -50 || position.x > 50
		|| position.y < -50 || position.y > 50
		|| position.z < -50 || position.z > 50)
	{
		ft_print_error(ERROR_CAMERA_BAD_POSITION, 0);
		return (1);
	}
	return (0);
}

int	ft_check_orientation(t_vec3 orientation)
{
	if (orientation.x < -1 || orientation.x > 1
		|| orientation.y < -1 || orientation.y > 1
		|| orientation.z < -1 || orientation.z > 1)
	{
		ft_print_error(ERROR_CAMERA_BAD_ORIENTATION, 0);
		return (1);
	}
	return (0);
}

t_color	ft_parse_color(char *str)
{
	char	**rgb;
	t_color	color;

	rgb = ft_split(str, ',');
	color.r = ft_atoi(rgb[0]);
	color.g = ft_atoi(rgb[1]);
	color.b = ft_atoi(rgb[2]);
	color.pixel_color = (color.r << 24) | (color.g << 16)
		| (color.b << 8) | 255;
	ft_free_split(rgb);
	return (color);
}

t_vec3	ft_parse_vec3(char *str)
{
	char	**xyz;
	t_vec3	vec3;

	xyz = ft_split(str, ',');
	vec3.x = ft_atof(xyz[0]);
	vec3.y = ft_atof(xyz[1]);
	vec3.z = ft_atof(xyz[2]);
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
