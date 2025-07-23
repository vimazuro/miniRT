/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_basis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 12:47:34 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:30:48 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_cam_basis	ft_camera_basis(t_camera camera)
{
	t_cam_basis	basis;
	t_vec3		world_up;

	world_up = vec3(0, 1, 0);
	basis.aspect_ratio = (float)WINDOW_W / (float)WINDOW_H;
	basis.scale = tanf((camera.fov * M_PI / 180.0f) / 2.0f);
	basis.forward = vec3_normalize(camera.orientation);
	basis.right = vec3_normalize(vec3_cross(world_up, basis.forward));
	basis.up = vec3_cross(basis.forward, basis.right);
	return (basis);
}
