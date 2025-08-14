/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_sphere_texture_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:11:48 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 12:56:49 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_get_uv_sphere(t_sphere *sp, t_texture_data_sphere *data,
	t_vec3 hit_point)
{
	t_vec3	p;

	p = vec3_sub(hit_point, sp->center);
	p = vec3_normalize(p);
	data->u = (0.5f + atan2f(p.z, p.x) / (2.0f * M_PI)) * 2.0f;
	data->u -= floorf(data->u);
	data->v = 0.5f - asinf(p.y) / M_PI;
}

t_color	ft_get_sphere_texture(mlx_texture_t *texture,
	t_texture_data_sphere *data)
{
	int		x;
	int		y;
	uint8_t	*pixel;
	t_color	color;

	x = (int)(data->u * (texture->width - 1));
	y = (int)(data->v * (texture->height - 1));
	pixel = &texture->pixels[4 * (y * texture->width + x)];
	color.r = pixel[0];
	color.g = pixel[1];
	color.b = pixel[2];
	color.pixel_color = (color.r << 24) | (color.g << 16)
		| (color.b << 8) | 255;
	return (color);
}
