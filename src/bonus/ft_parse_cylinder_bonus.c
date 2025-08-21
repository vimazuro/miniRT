/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cylinder_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:13:37 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/20 16:48:48 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	ft_init_cylinder_base(t_cylinder *cy, char **tokens)
{
	int	err;
	
	cy->point = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (1);
	cy->orientation = ft_parse_vec3(tokens[2], &err);
	if (err)
		return (1);
	cy->diameter = ft_atof(tokens[3], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		return (1);
	}
	cy->height = ft_atof(tokens[4], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		return (1);
	}
	cy->color = ft_parse_color(tokens[5]);
	cy->reflection = 0.0f;
	cy->has_checkerboard = false;
	cy->texture = NULL;
	cy->bump_map = NULL;
	return (0);
}

static int	ft_validate_cylinder_params(int count)
{
	if (count < 6 || count > 10)
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
		return (1);
	}
	return (0);
}

static int	ft_parse_cylinder_textures(t_cylinder *cy, char **tokens, int count)
{
	if (count >= 9)
	{
		cy->texture = ft_load_texture(tokens[8], ERROR_CYLINDER_TEXTURE_LOAD);
		if (!cy->texture)
			return (1);
	}
	if (count == 10)
	{
		cy->bump_map = ft_load_texture(tokens[9], ERROR_CYLINDER_BUMPMAP_LOAD);
		if (!cy->bump_map)
			return (1);
	}
	return (0);
}

static int	ft_parse_cylinder_optional(t_cylinder *cy, char **tokens, int count)
{
	int	err;
	
	if (count >= 7)
	{
		cy->reflection = ft_atof(tokens[6], &err);
		if (err)
		{
			ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
			return (1);
		}
		if (cy->reflection < 0.0f || cy->reflection > 1.0f)
		{
			ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
			return (1);
		}
	}
	if (count >= 8)
	{
		if (ft_parse_checkerboard(tokens, 7, &cy->has_checkerboard))
		{
			ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
			return (1);
		}
	}
	if (ft_parse_cylinder_textures(cy, tokens, count))
		return (1);
	return (0);
}

int	ft_parse_cylinder(t_data *data, char **tokens)
{
	t_cylinder	*cy;
	int			count;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_validate_cylinder_params(count))
		return (1);
	if (ft_check_coordinates(tokens[1]) || ft_check_coordinates(tokens[2]))
		return (1);
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		ft_print_error(ERROR_MALLOC, 0);
	if (ft_init_cylinder_base(cy, tokens))
	{
		free(cy);
		return (1);
	}
	if (ft_parse_cylinder_optional(cy, tokens, count))
	{
		free(cy);
		return (1);
	}
	if (ft_check_position(cy->point, "cylinder")
		|| ft_check_orientation(cy->orientation, "cylinder")
		|| cy->diameter <= 0 || cy->height <= 0 || ft_check_colors(&cy->color, "cylinder"))
	{
		free(cy);
		return (1);
	}
	cy->orientation = vec3_normalize(cy->orientation);
	ft_transfer_object(data, CYLINDER, cy);
	return (0);
}
