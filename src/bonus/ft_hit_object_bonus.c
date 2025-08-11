/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_object_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:20:18 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 14:59:41 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	hit_plane(t_ray ray, t_plane *plane,
	float *t_out, t_color *color_out)
{
	if (ft_intersect_plane(ray, *plane, t_out))
	{
		*color_out = plane->color;
		return (true);
	}
	return (false);
}

static bool	hit_sphere(t_ray ray, t_sphere *sphere,
	float *t_out, t_color *color_out)
{
	if (ft_intersect_sphere(ray, *sphere, t_out))
	{
		*color_out = sphere->color;
		return (true);
	}
	return (false);
}

static bool	hit_cylinder(t_ray ray, t_cylinder *cylinder,
	float *t_out, t_color *color_out)
{
	if (ft_intersect_cylinder(ray, *cylinder, t_out))
	{
		*color_out = cylinder->color;
		return (true);
	}
	return (false);
}

static bool	hit_cone(t_ray ray, t_cone *cone, float *t_out, t_color *color_out)
{
	if (ft_intersect_cone(ray, *cone, t_out))
	{
		*color_out = cone->color;
		return (true);
	}
	return (false);
}

bool	ft_hit_object(t_ray ray, t_object *obj, float *t_out,
	t_color *color_out)
{
	if (obj->type == PLANE)
		return (hit_plane(ray, (t_plane *)obj->data, t_out, color_out));
	else if (obj->type == SPHERE)
		return (hit_sphere(ray, (t_sphere *)obj->data, t_out, color_out));
	else if (obj->type == CYLINDER)
		return (hit_cylinder(ray, (t_cylinder *)obj->data, t_out, color_out));
	else if (obj->type == CONE)
		return (hit_cone(ray, (t_cone *)obj->data, t_out, color_out));
	return (false);
}
