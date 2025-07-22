/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:28:55 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:46:30 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
