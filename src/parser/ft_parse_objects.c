/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 15:40:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;
	t_object	*obj;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		ft_print_error(ERROR_MALLOC, 0);
	pl->point = ft_parse_vec3(tokens[1]);
	pl->normal = vec3_normalize(ft_parse_vec3(tokens[2]));
	pl->color = ft_parse_color(tokens[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = PLANE;
	obj->data = pl;
	obj->next = data->objects;
	data->objects = obj;
	return (0);
}

int	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;
	t_object	*obj;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		ft_print_error(ERROR_MALLOC, 0);
	sp->center = ft_parse_vec3(tokens[1]);
	sp->diameter = ft_atof(tokens[2]);
	sp->color = ft_parse_color(tokens[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = SPHERE;
	obj->data = sp;
	obj->next = data->objects;
	data->objects = obj;
	return (0);
}

int	ft_parse_cylinder(t_data *data, char **tokens)
{
	t_cylinder	*cy;
	t_object	*obj;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		ft_print_error(ERROR_MALLOC, 0);
	cy->point = ft_parse_vec3(tokens[1]);
	cy->orientation = vec3_normalize(ft_parse_vec3(tokens[2]));
	cy->diameter = ft_atof(tokens[3]);
	cy->height = ft_atof(tokens[4]);
	cy->color = ft_parse_color(tokens[5]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = CYLINDER;
	obj->data = cy;
	obj->next = data->objects;
	data->objects = obj;
	return (0);
}
