/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_bump_normal_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:21:48 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 15:29:13 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_prepare_bump_sampling(float u, float v,
	mlx_texture_t *bump_map, t_bump_sampling *s)
{
	s->x = (int)(u * bump_map->width) % bump_map->width;
	s->y = (int)(v * bump_map->height) % bump_map->height;
	s->x1 = (s->x + 1) % bump_map->width;
	s->y1 = (s->y + 1) % bump_map->height;
	s->pixel = &bump_map->pixels[4 * (s->y * bump_map->width + s->x)];
	s->pixel_right = &bump_map->pixels[4 * (s->y * bump_map->width + s->x1)];
	s->pixel_up = &bump_map->pixels[4 * (s->y1 * bump_map->width + s->x)];
	s->height_center = s->pixel[0] / 255.0f;
	s->height_right = s->pixel_right[0] / 255.0f;
	s->height_up = s->pixel_up[0] / 255.0f;
}

static t_vec3	ft_bump_plane(t_plane *pl, t_vec3 hit_point, t_vec3 base_normal)
{
	t_bump_data_plane	data;
	t_bump_sampling		s;
	t_vec3				tangent_offset;

	if (!pl->bump_map)
		return (base_normal);
	ft_get_bump_uv_plane(pl, &data, hit_point);
	ft_prepare_bump_sampling(data.u, data.v, pl->bump_map, &s);
	s.du = (s.height_right - s.height_center) * data.bump_strength;
	s.dv = (s.height_up - s.height_center) * data.bump_strength;
	tangent_offset = vec3_add(vec3_scale(data.u_vec, -s.du),
			vec3_scale(data.v_vec, -s.dv));
	return (vec3_normalize(vec3_add(base_normal, tangent_offset)));
}

static t_vec3	ft_bump_sphere(t_sphere *sp, t_vec3 hit_point,
	t_vec3 base_normal)
{
	t_bump_data_sphere	data;
	t_bump_sampling		s;
	t_vec3				tangent_offset;

	if (!sp->bump_map)
		return (base_normal);
	ft_get_bump_uv_sphere(sp, &data, hit_point);
	ft_prepare_bump_sampling(data.u, data.v, sp->bump_map, &s);
	s.du = (s.height_right - s.height_center) * data.bump_strength;
	s.dv = (s.height_up - s.height_center) * data.bump_strength;
	tangent_offset = vec3_add(vec3_scale(data.tangent, -s.du),
			vec3_scale(data.bitangent, -s.dv));
	return (vec3_normalize(vec3_add(base_normal, tangent_offset)));
}

static t_vec3	ft_bump_cylinder(t_cylinder *cy, t_vec3 hit_point,
	t_vec3 base_normal)
{
	t_bump_data_cylinder	data;
	t_bump_sampling			s;
	t_vec3					tangent_offset;

	if (!cy->bump_map)
		return (base_normal);
	ft_get_bump_uv_cylinder(cy, &data, hit_point);
	ft_prepare_bump_sampling(data.u, data.v, cy->bump_map, &s);
	s.du = (s.height_right - s.height_center) * data.bump_strength;
	s.dv = (s.height_up - s.height_center) * data.bump_strength;
	tangent_offset = vec3_add(vec3_scale(data.tangent, -s.du),
			vec3_scale(data.bitangent, -s.dv));
	return (vec3_normalize(vec3_add(base_normal, tangent_offset)));
}

t_vec3	ft_get_bump_normal(t_object *obj, t_vec3 hit_point, t_vec3 base_normal)
{
	if (obj->type == PLANE)
		return (ft_bump_plane((t_plane *)obj->data, hit_point, base_normal));
	else if (obj->type == SPHERE)
		return (ft_bump_sphere((t_sphere *)obj->data, hit_point, base_normal));
	else if (obj->type == CYLINDER)
		return (ft_bump_cylinder((t_cylinder *)obj->data,
				hit_point, base_normal));
	return (base_normal);
}
