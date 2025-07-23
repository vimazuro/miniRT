/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:58:23 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 15:29:21 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	ft_calc_lighting(t_hit_info hit, t_light *lights)
{
	t_color	result;
	t_vec3	light_dir;
	float	diff_intensity;
	t_color	light_contrib;

	result = (t_color){0, 0, 0, 0};
	while (lights)
	{
		light_dir = vec3_normalize(vec3_sub(lights->position, hit.hit_point));
		diff_intensity = fmaxf(vec3_dot(hit.normal, light_dir), 0.0f);
		light_contrib = color_scale(lights->color,
				lights->brightness * diff_intensity);
		result = color_add(result, color_multiply(hit.color, light_contrib));
		lights = lights->next;
	}
	return (result);
}
