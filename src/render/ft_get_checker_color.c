/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_checker_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:34 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/04 11:59:07 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_checker_data_plane(t_checker_data_plane *d,
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

static void	ft_init_checker_data_sphere(t_checker_data_sphere *d,
	t_object *obj, t_vec3 p)
{
	t_sphere	*sp;

	sp = (t_sphere *)obj->data;
	d->rel = vec3_sub(p, sp->center);
	d->theta = acosf(d->rel.y / (sp->diameter / 2));
	d->phi = atan2f(d->rel.z, d->rel.x);
	if (d->phi < 0)
		d->phi += 2.0f * M_PI;
	d->u = d->phi / (2.0f * M_PI);
	d->v = d->theta / M_PI;
	d->scale_u = 20.0f;
	d->scale_v = d->scale_u / 2.0f;
	d->x = floorf(d->u * d->scale_u);
	d->y = floorf(d->v * d->scale_v);
}

t_color	ft_get_checker_color(t_object *obj, t_vec3 p, t_color base_color)
{
	t_checker_data_plane	pl;
	t_checker_data_sphere	sp;

	if (obj->type == PLANE)
	{
		ft_init_checker_data_plane(&pl, obj, p);
		if ((pl.x + pl.y) % 2 == 0)
			return (base_color);
		else
			return ((t_color){0, 0, 0, 255});
	}
	else if (obj->type == SPHERE)
	{
		ft_init_checker_data_sphere(&sp, obj, p);
		if ((sp.x + sp.y) % 2 == 0)
			return (base_color);
		else
			return ((t_color){0, 0, 0, 255});
	}
	return (base_color);
}
