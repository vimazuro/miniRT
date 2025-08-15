/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cylinder_texture_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 12:02:41 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 14:48:25 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_get_uv_cylinder(t_cylinder *cy, t_texture_data_cylinder *data,
	t_vec3 hit_point)
{
	t_vec3	rel;
	t_vec3	axis;
	float	height_pos;
	float	angle;
	float	circumference;

	data->scale = 5.0f;
	data->u_fix = 2.0f;
	axis = vec3_normalize(cy->orientation);
	rel = vec3_sub(hit_point, cy->point);
	height_pos = vec3_dot(rel, axis);
	data->v = height_pos / data->scale;
	data->v -= floorf(data->v);
	angle = atan2f(rel.z - vec3_dot(axis, rel) * axis.z,
			rel.x - vec3_dot(axis, rel) * axis.x);
	if (angle < 0)
		angle += 2.0f * M_PI;
	circumference = M_PI * cy->diameter;
	data->u = (angle / (2.0f * M_PI)) * circumference
		/ data->scale * data->u_fix;
	data->u -= floorf(data->u);
}

t_color	ft_get_cylinder_texture(mlx_texture_t *texture,
	t_texture_data_cylinder *data)
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
