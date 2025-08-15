/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_texture_color_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:41:33 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 14:35:50 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_color	ft_get_plane_texture_color(t_plane *plane,
	t_vec3 hit_point, t_color fallback)
{
	t_texture_data_plane	data;

	if (!plane->texture)
		return (fallback);
	ft_init_texture_data_plane(plane, &data);
	ft_get_uv_plane(plane, &data, hit_point);
	return (ft_get_plane_texture(plane->texture, &data));
}

static t_color	ft_get_sphere_texture_color(t_sphere *sphere,
	t_vec3 hit_point, t_color fallback)
{
	t_texture_data_sphere	data;

	if (!sphere->texture)
		return (fallback);
	ft_get_uv_sphere(sphere, &data, hit_point);
	return (ft_get_sphere_texture(sphere->texture, &data));
}

static t_color	ft_get_cylinder_texture_color(t_cylinder *cylinder,
	t_vec3 hit_point, t_color fallback)
{
	t_texture_data_cylinder	data;

	if (!cylinder->texture)
		return (fallback);
	ft_get_uv_cylinder(cylinder, &data, hit_point);
	return (ft_get_cylinder_texture(cylinder->texture, &data));
}

t_color	ft_get_texture_color(t_object *obj, t_vec3 hit_point,
	t_color fallback)
{
	if (obj->type == PLANE)
		return (ft_get_plane_texture_color((t_plane *)obj->data,
				hit_point, fallback));
	else if (obj->type == SPHERE)
		return (ft_get_sphere_texture_color((t_sphere *)obj->data,
				hit_point, fallback));
	else if (obj->type == CYLINDER)
		return (ft_get_cylinder_texture_color((t_cylinder *)obj->data,
				hit_point, fallback));
	return (fallback);
}
