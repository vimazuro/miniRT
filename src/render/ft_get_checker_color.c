/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_checker_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:34 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/01 16:37:56 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_checker_data(t_checker_data	*d, t_object *obj)
{
	t_plane	*pl;

	if (obj->type == PLANE)
	{
		pl = (t_plane *)obj->data;
		d->normal = pl->normal;
		d->origin = pl->point;
	}
}

t_color	ft_get_checker_color(t_object *obj, t_vec3 p, t_color base_color)
{
	t_checker_data	d;

	ft_init_checker_data(&d, obj);
	if (fabsf(d.normal.x) < fabsf(d.normal.y)
		&& fabsf(d.normal.x) < fabsf(d.normal.z))
		d.ref = (t_vec3){1, 0, 0};
	else if (fabsf(d.normal.y) < fabsf(d.normal.z))
		d.ref = (t_vec3){0, 1, 0};
	else
		d.ref = (t_vec3){0, 0, 1};
	d.u = vec3_normalize(vec3_cross(d.ref, d.normal));
	d.v = vec3_normalize(vec3_cross(d.normal, d.u));
	d.rel = vec3_sub(p, d.origin);
	d.scale = 1;
	d.x = floorf((vec3_dot(d.rel, d.u)) / d.scale);
	d.y = floorf((vec3_dot(d.rel, d.v)) / d.scale);
	if ((d.x + d.y) % 2 == 0)
		return (base_color);
	else
		return ((t_color){0, 0, 0, 255});
	return (base_color);
}
