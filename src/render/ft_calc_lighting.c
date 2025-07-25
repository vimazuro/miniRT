/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_lighting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 16:58:23 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 10:45:12 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	ft_calc_lighting(t_hit_info hit, t_light *lights, t_ambient ambient)
{
	t_color	result;
	t_vec3	light_dir;
	float	diff_intensity;
	float	total_contribution = 0.0f;
	float	r_accum = 0.0f, g_accum = 0.0f, b_accum = 0.0f;
	
	result = color_scale(ambient.color, ambient.lighting);
	
	t_light *light_iter = lights;
	while (light_iter)
	{
		if (light_iter->brightness > 0.0f)
		{
			t_vec3 light_vector = vec3_sub(light_iter->position, hit.hit_point);
			float distance = vec3_length(light_vector);
			t_vec3 light_dir_norm = vec3_normalize(light_vector);
			
			float intensity = fmaxf(vec3_dot(hit.normal, light_dir_norm), 0.0f);
			float attenuation = 0.5f / (1.0f + 0.05f * distance + 0.005f * distance * distance);
			
			total_contribution += light_iter->brightness * intensity * attenuation;
		}
		light_iter = light_iter->next;
	}
	
	float normalization_factor = 1.0f;
	if (total_contribution > 1.0f)
		normalization_factor = 1.0f / total_contribution;
	
	while (lights)
	{
		if (lights->brightness > 0.0f)
		{
			t_vec3 light_vector = vec3_sub(lights->position, hit.hit_point);
			float distance = vec3_length(light_vector);
			light_dir = vec3_normalize(light_vector);
			
			diff_intensity = fmaxf(vec3_dot(hit.normal, light_dir), 0.0f);
			float attenuation = 1.0f / (1.0f + 0.05f * distance + 0.005f * distance * distance);
			
			float normalized_intensity = lights->brightness * diff_intensity * attenuation * normalization_factor;
			
			r_accum += lights->color.r * normalized_intensity;
			g_accum += lights->color.g * normalized_intensity;
			b_accum += lights->color.b * normalized_intensity;
		}
		lights = lights->next;
	}

	result.r = fminf(result.r + r_accum, 255.0f);
	result.g = fminf(result.g + g_accum, 255.0f);
	result.b = fminf(result.b + b_accum, 255.0f);
	
	return (color_multiply(hit.color, result));
}

/* t_color	ft_calc_lighting(t_hit_info hit, t_light *lights, t_ambient ambient)
{
	t_color	result;
	t_vec3	light_dir;
	float	diff_intensity;
	t_color	light_contrib;

	result = color_multiply(hit.color,
			color_scale(ambient.color, ambient.lighting));
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
} */
