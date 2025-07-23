/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:35:59 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:33:06 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_color	ft_trace_ray(t_ray ray, t_object *objects)
{
	float		t;
	float		closest_t;
	t_color		hit_color;
	t_color		final_color;
	t_object	*obj;

	closest_t = INFINITY;
	final_color = (t_color){0, 0, 0, 0};
	obj = objects;
	while (obj)
	{
		if (ft_hit_object(ray, obj, &t, &hit_color))
		{
			if (t < closest_t)
			{
				closest_t = t;
				final_color = hit_color;
			}
		}
		obj = obj->next;
	}
	return (final_color);
}

static void	ft_render_pixel(t_data *data, t_cam_basis basis, int x, int y)
{
	t_ray	ray;
	t_color	color;

	ray = ft_generate_ray(data->camera, basis, x, y);
	color = ft_trace_ray(ray, data->objects);
	mlx_put_pixel(data->img, x, y, color.pixel_color);
}

void	ft_render_scene(t_data *data)
{
	int			x;
	int			y;
	t_cam_basis	basis;

	basis = ft_camera_basis(data->camera);
	y = 0;
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < WINDOW_W)
		{
			ft_render_pixel(data, basis, x, y);
			x++;
		}
		y++;
	}
}
