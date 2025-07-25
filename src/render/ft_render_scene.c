/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:35:59 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 16:06:58 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_render_pixel(t_data *data, t_cam_basis basis, int x, int y)
{
	t_ray	ray;
	t_color	color;

	ray = ft_generate_ray(data->camera, basis, x, y);
	color = ft_trace_ray(ray, data->objects, data->lights, data->ambient);
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
