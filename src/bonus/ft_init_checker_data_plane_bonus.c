/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_checker_data_plane_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:34:46 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 13:53:45 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_init_checker_data_plane(t_checker_data_plane *d,
	t_object *obj, t_vec3 p)
{
	t_plane	*pl;

	if (obj->type == PLANE)
	{
		pl = (t_plane *)obj->data;
		d->normal = pl->normal;
		d->origin = pl->point;
		if (fabsf(d->normal.x) < fabsf(d->normal.y)
			&& fabsf(d->normal.x) < fabsf(d->normal.z))
			d->ref = (t_vec3){1, 0, 0};
		else if (fabsf(d->normal.y) < fabsf(d->normal.z))
			d->ref = (t_vec3){0, 1, 0};
		else
			d->ref = (t_vec3){0, 0, 1};
		d->u = vec3_normalize(vec3_cross(d->ref, d->normal));
		d->v = vec3_normalize(vec3_cross(d->normal, d->u));
		d->rel = vec3_sub(p, d->origin);
		d->scale = 1;
		d->x = floorf((vec3_dot(d->rel, d->u)) / d->scale);
		d->y = floorf((vec3_dot(d->rel, d->v)) / d->scale);
	}
}
