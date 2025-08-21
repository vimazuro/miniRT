/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 15:47:21 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/21 16:18:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_cylinder	*ft_init_cylinder(char **tokens)
{
	t_cylinder	*cy;
	int			count;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 6)
		return (ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0), NULL);
	if (ft_check_coordinates(tokens[1]) || ft_check_coordinates(tokens[2]))
		return (NULL);
	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
		return (ft_print_error(ERROR_MALLOC, 0), NULL);
	return (cy);
}

static int	ft_parse_cylinder_diameter(t_cylinder *cy, char *token)
{
	int	err;

	cy->diameter = ft_atof(token, &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(cy);
		return (1);
	}
	if (cy->diameter <= 0)
	{
		ft_print_error(ERROR_CYLINDER_BAD_DIAMETER, 0);
		free(cy);
		return (1);
	}
	return (0);
}

static int	ft_parse_cylinder_height(t_cylinder *cy, char *token)
{
	int	err;

	cy->height = ft_atof(token, &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(cy);
		return (1);
	}
	if (cy->height <= 0)
	{
		ft_print_error(ERROR_CYLINDER_BAD_HEIGHT, 0);
		free(cy);
		return (1);
	}
	return (0);
}

static void	ft_set_cylinder_defaults(t_cylinder *cy)
{
	cy->reflection = 0.0f;
	cy->has_checkerboard = false;
	cy->texture = NULL;
	cy->bump_map = NULL;
}

int	ft_parse_cylinder(t_data *data, char **tokens)
{
	t_cylinder	*cy;
	int			err;

	cy = ft_init_cylinder(tokens);
	if (!cy)
		return (1);
	cy->point = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (free(cy), 1);
	cy->orientation = ft_parse_vec3(tokens[2], &err);
	if (err)
		return (free(cy), 1);
	if (ft_parse_cylinder_diameter(cy, tokens[3])
		|| ft_parse_cylinder_height(cy, tokens[4]))
		return (1);
	cy->color = ft_parse_color(tokens[5]);
	ft_set_cylinder_defaults(cy);
	if (ft_check_position(cy->point, "cylinder")
		|| ft_check_orientation(cy->orientation, "cylinder")
		|| ft_check_colors(&cy->color, "cylinder"))
		return (free(cy), 1);
	cy->orientation = vec3_normalize(cy->orientation);
	ft_transfer_object(data, CYLINDER, cy);
	return (0);
}
