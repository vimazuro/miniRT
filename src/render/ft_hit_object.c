/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hit_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:20:18 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:49:46 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_hit_object(t_ray ray, t_object *obj, float *t_out,
	t_color *color_out)
{
	t_plane	*plane;

	if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->data;
		if (ft_intersect_plane(ray, *plane, t_out))
		{
			*color_out = plane->color;
			return (true);
		}
	}
	return (false);
}
