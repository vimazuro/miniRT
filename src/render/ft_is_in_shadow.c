/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 12:54:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/31 14:16:57 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_is_in_shadow(t_data *data, t_vec3 point, t_vec3 light_pos)
{
	t_ray		shadow_ray;
	t_hit_info	shadow_hit;
	t_vec3		to_light;
	float		distance_to_light;

	to_light = vec3_sub(light_pos, point);
	distance_to_light = vec3_length(to_light);
	shadow_ray.origin = vec3_add(point,
			vec3_scale(vec3_normalize(to_light), 0.001f));
	shadow_ray.direction = vec3_normalize(to_light);
	shadow_ray.depth = 0;
	shadow_ray.reflected = NULL;
	ft_init_hit_info(&shadow_hit);
	ft_find_closest_hit(shadow_ray, data->objects, &shadow_hit);
	if (shadow_hit.object && shadow_hit.t < distance_to_light)
		return (true);
	return (false);
}
