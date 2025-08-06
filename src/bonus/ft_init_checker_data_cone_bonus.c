/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_checker_data_cone_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:44:45 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 14:18:26 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_checker_axes_cone(t_checker_data_cone *d,
	t_cone *cone, t_vec3 p)
{
	d->rel = vec3_sub(p, cone->point);
	d->axis = vec3_normalize(cone->orientation);
	d->height = vec3_dot(d->rel, d->axis);
	d->proj = vec3_scale(d->axis, d->height);
	d->horiz = vec3_sub(d->rel, d->proj);
	if (fabsf(d->axis.x) < 0.9f)
		d->u_axis = vec3_normalize(vec3_cross((t_vec3){1, 0, 0}, d->axis));
	else
		d->u_axis = vec3_normalize(vec3_cross((t_vec3){0, 1, 0}, d->axis));
	d->v_axis = vec3_normalize(vec3_cross(d->axis, d->u_axis));
}

static void	ft_init_checker_uv_cone_part1(t_checker_data_cone *d,
	t_cone *cone, t_vec3 p)
{
	t_vec3	from_tip;

	d->theta = atan2f(vec3_dot(d->horiz, d->v_axis),
			vec3_dot(d->horiz, d->u_axis));
	if (d->theta < 0)
		d->theta += 2.0f * M_PI;
	d->u = d->theta / (2.0f * M_PI);
	d->scale_u = 8.0f;
	d->x = floorf(d->u * d->scale_u);
	from_tip = vec3_sub(p, cone->point);
	d->current_side = vec3_length(from_tip);
	d->angle_rad = cone->angle * (M_PI / 180.0f);
	d->base_radius = cone->height * tanf(d->angle_rad / 2.0f);
	d->side_length = sqrtf(cone->height * cone->height
			+ d->base_radius * d->base_radius);
}

static void	ft_init_checker_uv_cone_part2(t_checker_data_cone *d)
{
	float	accum;
	float	t;
	float	r;
	float	arc;
	float	h;

	accum = 1e-4f;
	d->y = 0;
	while (accum < d->current_side && d->y < 1000)
	{
		t = accum / d->side_length;
		r = d->base_radius * t;
		arc = (2.0f * M_PI * r) / d->scale_u;
		h = 2.0f * arc * cosf(d->angle_rad / 2.0f);
		if (h < 1e-4f)
			h = 1e-4f;
		accum += h;
		d->y++;
	}
}

void	ft_init_checker_data_cone(t_checker_data_cone *d,
	t_object *obj, t_vec3 p)
{
	t_cone	*cone;

	cone = (t_cone *)obj->data;
	ft_init_checker_axes_cone(d, cone, p);
	ft_init_checker_uv_cone_part1(d, cone, p);
	ft_init_checker_uv_cone_part2(d);
}
