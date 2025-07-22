/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 13:40:03 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:49:01 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	ft_generate_ray(t_camera cam, t_cam_basis basis, int x, int y)
{
	t_ray	ray;
	float	px;
	float	py;
	t_vec3	offset_right;
	t_vec3	offset_up;

	px = (2.0f * ((x + 0.5f) / WINDOW_W) - 1.0f)
		* basis.aspect_ratio * basis.scale;
	py = (1.0f - 2.0f * ((y + 0.5f) / WINDOW_H))
		* basis.scale;
	offset_right = vec3_scale(basis.right, px);
	offset_up = vec3_scale(basis.up, py);
	ray.origin = cam.position;
	ray.direction = vec3_normalize(vec3_add(vec3_add(offset_right,
					offset_up), basis.forward));
	return (ray);
}
