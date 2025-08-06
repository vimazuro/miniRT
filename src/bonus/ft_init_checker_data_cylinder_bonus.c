/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_checker_data_cylinder_bonus.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:56:17 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 14:18:55 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_checker_axes(t_checker_data_cylinder *d,
	t_cylinder *cy, t_vec3 p)
{
	d->rel = vec3_sub(p, cy->point);
	d->axis = vec3_normalize(cy->orientation);
	d->height = vec3_dot(d->rel, d->axis);
	d->proj = vec3_scale(d->axis, d->height);
	d->horiz = vec3_sub(d->rel, d->proj);
	if (fabsf(d->axis.x) < 0.9f)
		d->u_axis = vec3_normalize(vec3_cross((t_vec3){1, 0, 0}, d->axis));
	else
		d->u_axis = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, d->axis));
	d->v_axis = vec3_normalize(vec3_cross(d->axis, d->u_axis));
}

static void	ft_init_checker_uv(t_checker_data_cylinder *d, t_cylinder *cy)
{
	float	circumference;

	d->tmp_x = vec3_dot(d->horiz, d->u_axis);
	d->tmp_y = vec3_dot(d->horiz, d->v_axis);
	d->theta = atan2f(d->tmp_y, d->tmp_x);
	if (d->theta < 0)
		d->theta += 2.0f * M_PI;
	d->u = d->theta / (2.0f * M_PI);
	d->v = (d->height + cy->height / 2.0f) / cy->height;
	d->scale_u = 20.0f;
	circumference = 2.0f * M_PI * (cy->diameter / 2);
	d->scale_v = (d->scale_u * cy->height) / circumference;
	d->x = floorf(d->u * d->scale_u);
	d->y = floorf(d->v * d->scale_v);
}

void	ft_init_checker_data_cylinder(t_checker_data_cylinder *d,
	t_object *obj, t_vec3 p)
{
	t_cylinder	*cy;

	cy = (t_cylinder *)obj->data;
	ft_init_checker_axes(d, cy, p);
	ft_init_checker_uv(d, cy);
}
