/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_plane_texture_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:08:14 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 11:17:32 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_init_texture_data_plane(t_plane *pl, t_texture_data_plane *data)
{
	if (fabsf(pl->normal.y) > 0.999f)
	{
		data->u_vec = vec3_normalize((t_vec3){1, 0, 0});
		data->v_vec = vec3_normalize((t_vec3){0, 0, 1});
	}
	else
	{
		data->u_vec = vec3_normalize(vec3_cross(pl->normal, (t_vec3){0, 1, 0}));
		data->v_vec = vec3_cross(pl->normal, data->u_vec);
	}
	data->texture_scale = 0.1f;
}

void	ft_get_uv_plane(t_plane *pl, t_texture_data_plane *data,
	t_vec3 hit_point)
{
	t_vec3	hit_to_origin;

	hit_to_origin = vec3_sub(hit_point, pl->point);
	data->u_coord = vec3_dot(hit_to_origin, data->u_vec) * data->texture_scale;
	data->v_coord = vec3_dot(hit_to_origin, data->v_vec) * data->texture_scale;
	data->u = data->u_coord - floorf(data->u_coord);
	data->v = data->v_coord - floorf(data->v_coord);
}

t_color	ft_get_plane_texture(mlx_texture_t *texture, t_texture_data_plane *data)
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
