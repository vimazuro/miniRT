/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:44:21 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/24 16:36:08 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_hit_info(t_hit_info *hit_info)
{
	hit_info->t = INFINITY;
	hit_info->color = (t_color){0, 0, 0, 255};
	hit_info->hit_point = (t_vec3){0, 0, 0};
	hit_info->normal = (t_vec3){0, 0, 0};
	hit_info->object = NULL;
}

static void	ft_find_closest_hit(t_ray ray, t_object *objects,
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

t_color	ft_trace_ray(t_ray ray, t_object *objects,
	t_light *lights, t_ambient ambient)
{
	t_hit_info	hit_info;

	ft_init_hit_info(&hit_info);
	ft_find_closest_hit(ray, objects, &hit_info);
	if (!hit_info.object)
		return (hit_info.color);
	hit_info.hit_point = vec3_add(ray.origin,
			vec3_scale(ray.direction, hit_info.t));
	hit_info.normal = ft_get_normal(hit_info.object, hit_info.hit_point);
	return (ft_calc_lighting(hit_info, lights, ambient));
}
