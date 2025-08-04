/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_checker_data_sphere.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:53:51 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/04 17:10:51 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_init_checker_data_sphere(t_checker_data_sphere *d,
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
