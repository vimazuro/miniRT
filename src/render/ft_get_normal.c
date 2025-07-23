/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:10:50 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 15:27:01 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vec3	ft_get_normal(t_object *obj, t_vec3 point)
{
	t_plane		*plane;
	t_sphere	*sphere;

	if (obj->type == PLANE)
	{
		plane = (t_plane *)obj->data;
		return (plane->normal);
	}
	else if (obj->type == SPHERE)
	{
		sphere = (t_sphere *)obj->data;
		return (vec3_normalize(vec3_sub(point, sphere->center)));
	}
	return ((t_vec3){0, 0, 0});
}
