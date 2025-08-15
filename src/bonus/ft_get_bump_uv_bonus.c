/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bump_uv_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:14:43 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 15:48:42 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_get_bump_uv_plane(t_plane *pl, t_bump_data_plane *data,
	t_vec3 hit_point)
{
	t_vec3	hit_to_origin;

	if (fabsf(pl->normal.y) > 0.999f)
	{
		data->u_vec = vec3_normalize((t_vec3){1, 0, 0});
		data->v_vec = vec3_normalize((t_vec3){0, 0, 1});
	}
	else
	{
		data->u_vec = vec3_normalize(vec3_cross(pl->normal, (t_vec3){0, 1, 0}));
		data->v_vec = vec3_cross(pl->normal, data->u_vec);
	}
	data->texture_scale = 0.1f;
	data->bump_strength = 100.0f;
	hit_to_origin = vec3_sub(hit_point, pl->point);
	data->u_coord = vec3_dot(hit_to_origin, data->u_vec) * data->texture_scale;
	data->v_coord = vec3_dot(hit_to_origin, data->v_vec) * data->texture_scale;
	data->u = data->u_coord - floorf(data->u_coord);
	data->v = data->v_coord - floorf(data->v_coord);
}

void	ft_get_bump_uv_sphere(t_sphere *sp, t_bump_data_sphere *data,
	t_vec3 hit_point)
{
	t_vec3	p;

	p = vec3_sub(hit_point, sp->center);
	p = vec3_normalize(p);
	data->u = 0.5f + atan2f(p.z, p.x) / (2.0f * M_PI);
	data->v = 0.5f - asinf(p.y) / M_PI;
	data->tangent = vec3_normalize((t_vec3){-p.z, 0, p.x});
	data->bitangent = vec3_normalize(vec3_cross(p, data->tangent));
	data->bump_strength = 100.0f;
}

void	ft_get_bump_uv_cylinder(t_cylinder *cy, t_bump_data_cylinder *data,
	t_vec3 hit_point)
{
	t_vec3	rel;
	t_vec3	ortho;
	float	height_pos;
	float	angle;
	float	circumference;

	data->scale = 5.0f;
	data->u_fix = 2.0f;
	data->bump_strength = 100.0f;
	data->axis = vec3_normalize(cy->orientation);
	rel = vec3_sub(hit_point, cy->point);
	height_pos = vec3_dot(rel, data->axis);
	data->v = height_pos / data->scale;
	data->v -= floorf(data->v);
	ortho = vec3_sub(rel, vec3_scale(data->axis, height_pos));
	angle = atan2f(ortho.z, ortho.x);
	if (angle < 0)
		angle += 2.0f * M_PI;
	circumference = M_PI * cy->diameter;
	data->u = (angle / (2.0f * M_PI)) * circumference
		/ data->scale * data->u_fix;
	data->u -= floorf(data->u);
	data->tangent = vec3_normalize((t_vec3){-ortho.z, 0, ortho.x});
	data->bitangent = vec3_cross(data->axis, data->tangent);
}
