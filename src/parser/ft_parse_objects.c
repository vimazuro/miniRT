/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 10:01:41 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_transfer_object(t_data *data, int type, void *object_data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = type;
	obj->data = object_data;
	obj->next = data->objects;
	data->objects = obj;
}

int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0);
		return (1);
	}
	pl = malloc(sizeof(t_plane));
	if (!pl)
		ft_print_error(ERROR_MALLOC, 0);
	pl->point = ft_parse_vec3(tokens[1]);
	pl->normal = vec3_normalize(ft_parse_vec3(tokens[2]));
	pl->color = ft_parse_color(tokens[3]);
	if (ft_check_position(pl->point) || ft_check_orientation(pl->normal)
		|| ft_check_colors(&pl->color))
	{
		free(pl);
		return (1);
	}
	ft_transfer_object(data, PLANE, pl);
	return (0);
}

int	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
	{
		ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0);
		return (1);
	}
	sp = malloc(sizeof(t_sphere));
	if (!sp)
		ft_print_error(ERROR_MALLOC, 0);
	sp->center = ft_parse_vec3(tokens[1]);
	sp->diameter = ft_atof(tokens[2]);
	sp->color = ft_parse_color(tokens[3]);
	if (ft_check_position(sp->center) || sp->diameter <= 0
		|| ft_check_colors(&sp->color))
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

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5] || tokens[6])
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
		return (1);
	}
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		ft_print_error(ERROR_MALLOC, 0);
	cy->point = ft_parse_vec3(tokens[1]);
	cy->orientation = vec3_normalize(ft_parse_vec3(tokens[2]));
	cy->diameter = ft_atof(tokens[3]);
	cy->height = ft_atof(tokens[4]);
	cy->color = ft_parse_color(tokens[5]);
	if (ft_check_position(cy->point) || ft_check_orientation(cy->orientation)
		|| cy->diameter <= 0 || cy->height <= 0 || ft_check_colors(&cy->color))
	{
		free(cy);
		return (1);
	}
	ft_transfer_object(data, CYLINDER, cy);
	return (0);
}

int ft_parse_cone(t_data *data, char **tokens)
{
	t_cone	*cone;

	if (!tokens[0] || !tokens[1] || !tokens[2] || !tokens[3]
		|| !tokens[4] || !tokens[5] || tokens[6])
	{
		ft_print_error(ERROR_OBJECTS_CONE_BAD_PARAMS, 0);
		return (1);
	}
	cone = malloc(sizeof(t_cone));
	if (!cone)
		ft_print_error(ERROR_MALLOC, 0);
	cone->point = ft_parse_vec3(tokens[1]);
	cone->orientation = vec3_normalize(ft_parse_vec3(tokens[2]));
	cone->angle = ft_atof(tokens[3]);
	cone->height = ft_atof(tokens[4]);
	cone->color = ft_parse_color(tokens[5]);
	if (ft_check_position(cone->point) || ft_check_orientation(cone->orientation)
		|| cone->angle <= 0 || cone->height <= 0 || ft_check_colors(&cone->color))
	{
		free(cone);
		return (1);
	}
	ft_transfer_object(data, CONE, cone);
	return (0);
}
