/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_ray_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:44:21 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 14:37:36 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_init_hit_info(t_hit_info *hit_info)
{
	hit_info->t = INFINITY;
	hit_info->color = (t_color){0, 0, 0, 255};
	hit_info->hit_point = (t_vec3){0, 0, 0};
	hit_info->normal = (t_vec3){0, 0, 0};
	hit_info->object = NULL;
	hit_info->reflection = 0.0f;
}

void	ft_find_closest_hit(t_ray ray, t_object *objects,
	t_hit_info *hit_info)
{
	t_object	*obj;
	float		t;
	t_color		hit_color;

	obj = objects;
	while (obj)
	{
		if (ft_hit_object(ray, obj, &t, &hit_color))
		{
			if (t < hit_info->t)
			{
				hit_info->t = t;
				hit_info->color = hit_color;
				hit_info->object = obj;
			}
		}
		obj = obj->next;
	}
}

static void	ft_process_reflection(t_data *data, t_ray *ray, t_hit_info hit_info)
{
	ray->reflected = malloc(sizeof(t_ray));
	if (!ray->reflected)
		ft_print_error(ERROR_MALLOC, 0);
	ray->reflected->origin = vec3_add(hit_info.hit_point,
			vec3_scale(hit_info.normal, 0.001f));
	ray->reflected->direction = vec3_normalize(vec3_reflect(ray->direction,
				hit_info.normal));
	ray->reflected->depth = ray->depth + 1;
	ray->reflected->reflected = NULL;
	ray->reflected->color = ft_trace_ray(data, *ray->reflected);
	ray->color = color_lerp(ray->color, ray->reflected->color,
			hit_info.reflection);
}

t_color	ft_trace_ray(t_data *data, t_ray ray)
{
	t_hit_info	hit_info;

	ft_init_hit_info(&hit_info);
	ft_find_closest_hit(ray, data->objects, &hit_info);
	if (!hit_info.object)
		return (hit_info.color);
	hit_info.hit_point = vec3_add(ray.origin,
			vec3_scale(ray.direction, hit_info.t));
	hit_info.normal = ft_get_normal(hit_info.object, hit_info.hit_point);
	hit_info.reflection = ft_get_reflection(hit_info.object);
	ray.color = ft_calc_lighting(hit_info, data);
	if (hit_info.reflection > 0.0f && ray.depth < MAX_DEPTH)
		ft_process_reflection(data, &ray, hit_info);
	if (ray.reflected)
	{
		free(ray.reflected);
		ray.reflected = NULL;
	}
	return (ray.color);
}
