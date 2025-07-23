/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 14:15:00 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:32:04 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_intersect_plane(t_ray ray, t_plane plane, float *t_out)
{
	float	denom;
	float	t;
	t_vec3	diff;

	denom = vec3_dot(ray.direction, plane.normal);
	if (fabsf(denom) < 1e-6)
		return (false);
	diff = vec3_sub(plane.point, ray.origin);
	t = vec3_dot(diff, plane.normal) / denom;
	if (t < 0)
		return (false);
	*t_out = t;
	return (true);
}
