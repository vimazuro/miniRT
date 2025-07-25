/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:58:23 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 11:16:52 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	ft_calc_lighting(t_hit_info hit, t_light *lights, t_ambient ambient)
{
	t_color			result;
	t_light_calc	lc;

	result = color_multiply(hit.color,
			color_scale(ambient.color, ambient.lighting));
	while (lights)
	{
		if (lights->brightness > 0.0f)
		{
			lc.light_vector = vec3_sub(lights->position, hit.hit_point);
			lc.distance = vec3_length(lc.light_vector);
			lc.light_dir = vec3_normalize(lc.light_vector);
			lc.diff_intensity = fmaxf(vec3_dot(hit.normal, lc.light_dir), 0.0f);
			lc.attenuation = 1.0f / (1.0f + 0.09f * lc.distance
					+ 0.032f * lc.distance * lc.distance);
			lc.light_contrib = color_scale(lights->color,
					lights->brightness * lc.diff_intensity * lc.attenuation);
			result = color_add(result, color_multiply(hit.color,
						lc.light_contrib));
		}
		lights = lights->next;
	}
	return (result);
}
