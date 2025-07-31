/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:10:50 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/29 12:01:26 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vec3	get_plane_normal(t_object *obj)
{
	t_plane		*plane;

	plane = (t_plane *)obj->data;
	return (plane->normal);
}

static t_vec3	get_sphere_normal(t_object *obj, t_vec3 point)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)obj->data;
	return (vec3_normalize(vec3_sub(point, sphere->center)));
}

static t_vec3	get_cylinder_normal(t_object *obj, t_vec3 point)
{
	t_cylinder	*cylinder;
	t_vec3		to_point;
	t_vec3		axis_projection;
	t_vec3		radial_vector;

	cylinder = (t_cylinder *)obj->data;
	to_point = vec3_sub(point, cylinder->point);
	axis_projection = vec3_scale(cylinder->orientation,
			vec3_dot(to_point, cylinder->orientation));
	radial_vector = vec3_sub(to_point, axis_projection);
	return (vec3_normalize(radial_vector));
}

static t_vec3	get_cone_normal(t_object *obj, t_vec3 point)
{
	t_cone				*cone;
	t_cone_normal_data	d;

	cone = (t_cone *)obj->data;
	d.to_hit = vec3_sub(point, cone->point);
	d.projection = vec3_dot(d.to_hit, cone->orientation);
	d.axis_to_hit = vec3_sub(d.to_hit,
			vec3_scale(cone->orientation, d.projection));
	d.cos_theta = cosf(cone->angle * M_PI / 180.0f);
	d.sin_theta = sinf(cone->angle * M_PI / 180.0f);
	d.radial_dir = vec3_normalize(d.axis_to_hit);
	d.axial_component = vec3_scale(cone->orientation, -d.sin_theta);
	d.radial_component = vec3_scale(d.radial_dir, d.cos_theta);
	d.normal = vec3_add(d.axial_component, d.radial_component);
	return (vec3_normalize(d.normal));
}

t_vec3	ft_get_normal(t_object *obj, t_vec3 point)
{
	if (obj->type == PLANE)
		return (get_plane_normal(obj));
	else if (obj->type == SPHERE)
		return (get_sphere_normal(obj, point));
	else if (obj->type == CYLINDER)
		return (get_cylinder_normal(obj, point));
	else if (obj->type == CONE)
		return (get_cone_normal(obj, point));
	return ((t_vec3){0, 0, 0});
}
