/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:22:59 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 15:30:52 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	color_scale(t_color color, float factor)
{
	t_color	result;

	result.r = fmin(color.r * factor, 255.0f);
	result.g = fmin(color.g * factor, 255.0f);
	result.b = fmin(color.b * factor, 255.0f);
	result.pixel_color = (result.r << 24) | (result.g << 16)
		| (result.b << 8) | 255;
	return (result);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = fminf(c1.r + c2.r, 255.0f);
	result.g = fminf(c1.g + c2.g, 255.0f);
	result.b = fminf(c1.b + c2.b, 255.0f);
	result.pixel_color = (result.r << 24) | (result.g << 16)
		| (result.b << 8) | 255;
	return (result);
}

t_color	color_multiply(t_color c1, t_color c2)
{
	t_color	result;

	result.r = (c1.r * c2.r) / 255;
	result.g = (c1.g * c2.g) / 255;
	result.b = (c1.b * c2.b) / 255;
	result.pixel_color = (result.r << 24) | (result.g << 16)
		| (result.b << 8) | 255;
	return (result);
}
