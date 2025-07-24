/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:20:18 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/24 12:06:44 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_hit_object(t_ray ray, t_object *obj, float *t_out,
	t_color *color_out)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->data;
		if (ft_intersect_plane(ray, *plane, t_out))
		{
			*color_out = plane->color;
			return (true);
		}
	}
	else if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->data;
		if (ft_intersect_sphere(ray, *sphere, t_out))
		{
			*color_out = sphere->color;
			return (true);
		}
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cylinder *)obj->data;
		if (ft_intersect_cylinder(ray, *cylinder, t_out))
		{
			*color_out = cylinder->color;
			return (true);
		}
	}
	return (false);
}