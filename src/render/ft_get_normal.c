/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:10:50 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 10:49:10 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vec3	ft_cylinder_normal(t_cylinder *cylinder, t_vec3 point)
{
	t_vec3	to_point;
	t_vec3	axis_projection;
	t_vec3	radial_vector;

	to_point = vec3_sub(point, cylinder->point);
	axis_projection = vec3_scale(cylinder->orientation, 
		vec3_dot(to_point, cylinder->orientation));
	radial_vector = vec3_sub(to_point, axis_projection);
	
	return (vec3_normalize(radial_vector));
}

t_vec3 ft_get_cone_normal(t_cone cone, t_vec3 hit_point)
{
	t_vec3  to_hit;
	float   projection;
	t_vec3  axis_to_hit;
	t_vec3  normal;
	float   cos_theta;
	float   sin_theta;

	to_hit = vec3_sub(hit_point, cone.point);
	projection = vec3_dot(to_hit, cone.orientation);
	
	axis_to_hit = vec3_sub(to_hit, vec3_scale(cone.orientation, projection));
	
	cos_theta = cosf(cone.angle * M_PI / 180.0f);
	sin_theta = sinf(cone.angle * M_PI / 180.0f);
	
	t_vec3 radial_dir = vec3_normalize(axis_to_hit);
	t_vec3 axial_component = vec3_scale(cone.orientation, -sin_theta);
	t_vec3 radial_component = vec3_scale(radial_dir, cos_theta);
	
	normal = vec3_add(axial_component, radial_component);
	return (vec3_normalize(normal));
}

t_vec3	ft_get_normal(t_object *obj, t_vec3 point)
{
	t_plane		*plane;
	t_sphere	*sphere;
	t_cylinder	*cylinder;

	if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->data;
		return (plane->normal);
	}
	else if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->data;
		return (vec3_normalize(vec3_sub(point, sphere->center)));
	}
	else if (obj->type == CYLINDER)
	{
		cylinder = (t_cylinder *)obj->data;
		return (ft_cylinder_normal(cylinder, point));
	}
	else if (obj->type == CONE)
	{
		t_cone *cone = (t_cone *)obj->data;
		return (ft_get_cone_normal(*cone, point));
	}
	return ((t_vec3){0, 0, 0});
}