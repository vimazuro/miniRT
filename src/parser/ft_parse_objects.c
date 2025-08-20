/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/20 14:35:49 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;
	int			count;
	int			err;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 4)
	{
		ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0);
		return (1);
	}
	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		ft_print_error(ERROR_MALLOC, 0);
	pl->point = ft_parse_vec3(tokens[1], &err);
	if (err)
	{
		free(pl);
		return (1);
	}
	pl->normal = ft_parse_vec3(tokens[2], &err);
	if (err)
	{
		free(pl);
		return (1);
	}
	pl->color = ft_parse_color(tokens[3]);
	pl->reflection = 0.0f;
	pl->has_checkerboard = false;
	pl->texture = NULL;
	pl->bump_map = NULL;
	if (ft_check_position(pl->point, "plane") || ft_check_coordinates(tokens[1])
		|| ft_check_orientation(pl->normal, "plane")
		|| ft_check_coordinates(tokens[2])
		|| ft_check_colors(&pl->color, "plane"))
	{
		free(pl);
		return (1);
	}
	pl->normal = vec3_normalize(pl->normal);
	ft_transfer_object(data, PLANE, pl);
	return (0);
}

int	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;
	int			count;
	int			err;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 4)
	{
		ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0);
		return (1);
	}
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
	{
		ft_print_error(ERROR_MALLOC, 0);
		return (1);
	}
	sp->center = ft_parse_vec3(tokens[1], &err);
	if (err)
	{
		free(sp);
		return (1);
	}
	sp->diameter = ft_atof(tokens[2], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(sp);
		return (1);
	}
	if (sp->diameter <= 0)
	{
		
		ft_print_error(ERROR_OBJECTS_SPHERE_BAD_DIAMETER, 0);
		free(sp);
		return (1);
	}
	sp->color = ft_parse_color(tokens[3]);
	sp->reflection = 0.0f;
	sp->has_checkerboard = false;
	sp->texture = NULL;
	sp->bump_map = NULL;
	if (ft_check_position(sp->center, "sphere") || ft_check_coordinates(tokens[1])
		|| sp->diameter <= 0
		|| ft_check_colors(&sp->color, "sphere"))
	{
		free(sp);
		return (1);
	}
	ft_transfer_object(data, SPHERE, sp);
	return (0);
}

int	ft_parse_cylinder(t_data *data, char **tokens)
{
	t_cylinder	*cy;
	int			count;
	int			err;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 6)
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
		return (1);
	}
	cy = ft_calloc(1, sizeof(t_cylinder));
	if (!cy)
	{
		ft_print_error(ERROR_MALLOC, 0);
		return (1);
	}
	cy->point = ft_parse_vec3(tokens[1], &err);
	if (err)
	{
		free(cy);
		return (1);
	}
	cy->orientation = ft_parse_vec3(tokens[2], &err);
	if (err)
	{
		free(cy);
		return (1);
	}
	cy->diameter = ft_atof(tokens[3], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(cy);
		return (1);
	}
	cy->height = ft_atof(tokens[4], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(cy);
		return (1);
	}
	cy->color = ft_parse_color(tokens[5]);
	cy->reflection = 0.0f;
	cy->has_checkerboard = false;
	cy->texture = NULL;
	cy->bump_map = NULL;
	if (ft_check_position(cy->point, "cylinder") || ft_check_coordinates(tokens[1])
	|| ft_check_orientation(cy->orientation, "cylinder")
	|| ft_check_coordinates(tokens[2])
	|| ft_check_colors(&cy->color, "cylinder"))
	{
		free(cy);
		return (1);
	}
	if (cy->diameter <= 0)
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_DIAMETER, 0);
		free(cy);
		return (1);
	}
	if (cy->height <= 0)
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_HEIGHT, 0);
		free(cy);
		return (1);
	}

	cy->orientation = vec3_normalize(cy->orientation);
	ft_transfer_object(data, CYLINDER, cy);
	return (0);
}
