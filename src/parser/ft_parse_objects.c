/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:36:10 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;
	t_object	*obj;

	pl = malloc(sizeof(t_plane));
	if (!pl)
		ft_print_error("malloc error\n");
	pl->point = ft_parse_vec3(tokens[1]);
	pl->normal = vec3_normalize(ft_parse_vec3(tokens[2]));
	pl->color = ft_parse_color(tokens[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error("malloc error\n");
	obj->type = PLANE;
	obj->data = pl;
	obj->next = data->objects;
	data->objects = obj;
}

void	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;
	t_object	*obj;

	sp = malloc(sizeof(t_sphere));
	if (!sp)
		ft_print_error("malloc error\n");
	sp->center = ft_parse_vec3(tokens[1]);
	sp->diameter = ft_atof(tokens[2]);
	sp->color = ft_parse_color(tokens[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error("malloc error\n");
	obj->type = SPHERE;
	obj->data = sp;
	obj->next = data->objects;
	data->objects = obj;
}
