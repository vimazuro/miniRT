/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:58:23 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/15 14:20:25 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_color	ft_apply_light(t_hit_info hit, t_light *light)
{
	t_light_calc	lc;
	t_color			white;

	white = color_create(255, 255, 255);
	lc.light_vector = vec3_sub(light->position, hit.hit_point);
	lc.distance = vec3_length(lc.light_vector);
	lc.light_dir = vec3_normalize(lc.light_vector);
	lc.diff_intensity = fmaxf(vec3_dot(hit.normal,
				lc.light_dir), 0.0f);
	lc.attenuation = 1.0f / (1.0f + 0.09f * lc.distance
			+ 0.032f * lc.distance * lc.distance);
	lc.light_contrib = color_scale(white, light->brightness
			* lc.diff_intensity * lc.attenuation);
	return (color_multiply(hit.color, lc.light_contrib));
}

t_color	ft_calc_lighting(t_hit_info hit, t_data *data)
{
	t_color			result;
	t_light			*lights;

	result = color_multiply(hit.color,
			color_scale(data->ambient.color, data->ambient.lighting));
	lights = data->lights;
	while (lights)
	{
		if (lights->brightness > 0.0f
			&& !ft_is_in_shadow(data, hit.hit_point, lights->position))
			result = color_add(result, ft_apply_light(hit, lights));
		lights = lights->next;
	}
	return (result);
}
