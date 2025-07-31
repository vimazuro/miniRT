/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:48:12 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/29 14:48:17 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	ft_check_cone_bounds(t_ray ray, t_cone cone, float t)
{
	t_vec3	hit_point;
	t_vec3	to_hit;
	float	projection;
	float	radius_at_height;
	float	perp_distance;

	hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	to_hit = vec3_sub(hit_point, cone.point);
	projection = vec3_dot(to_hit, cone.orientation);
	if (projection < -1e-4 || projection > cone.height + 1e-4)
		return (false);
	radius_at_height = tanf(cone.angle * M_PI / 180.0f) * projection;
	if (projection < 1e-2)
		return (true);
	perp_distance = vec3_length(vec3_sub(to_hit,
				vec3_scale(cone.orientation, projection)));
	return (perp_distance <= radius_at_height + 1e-4);
}

static bool	ft_solve_cone_quadratic(t_quadratic *q, t_ray ray,
									t_cone cone, float *t_out)
{
	float	sqrt_d;
	float	temp;

	if (q->discriminant < 0)
		return (false);
	sqrt_d = sqrtf(q->discriminant);
	q->t1 = (-q->b - sqrt_d) / (2.0f * q->a);
	q->t2 = (-q->b + sqrt_d) / (2.0f * q->a);
	if (q->t1 > q->t2)
	{
		temp = q->t1;
		q->t1 = q->t2;
		q->t2 = temp;
	}
	if (q->t1 > 1e-3 && ft_check_cone_bounds(ray, cone, q->t1))
	{
		*t_out = q->t1;
		return (true);
	}
	if (q->t2 > 1e-3 && ft_check_cone_bounds(ray, cone, q->t2))
	{
		*t_out = q->t2;
		return (true);
	}
	return (false);
}

static void	ft_cone_coeffs(t_ray ray, t_cone cone, t_quadratic *q)
{
	t_cone_calc	c;

	c.oc = vec3_sub(ray.origin, cone.point);
	c.tan_theta = tanf(cone.angle * M_PI / 180.0f);
	c.tan_theta_sq = c.tan_theta * c.tan_theta;
	c.d_dot_v = vec3_dot(ray.direction, cone.orientation);
	c.oc_dot_v = vec3_dot(c.oc, cone.orientation);
	c.d_dot_d = vec3_dot(ray.direction, ray.direction);
	c.oc_dot_d = vec3_dot(c.oc, ray.direction);
	c.oc_dot_oc = vec3_dot(c.oc, c.oc);
	q->a = c.d_dot_d - c.d_dot_v * c.d_dot_v * (1.0f + c.tan_theta_sq);
	q->b = 2.0f * (c.oc_dot_d - c.oc_dot_v * c.d_dot_v
			* (1.0f + c.tan_theta_sq));
	q->c = c.oc_dot_oc - c.oc_dot_v * c.oc_dot_v * (1.0f + c.tan_theta_sq);
	q->discriminant = q->b * q->b - 4.0f * q->a * q->c;
}

bool	ft_intersect_cone(t_ray ray, t_cone cone, float *t_out)
{
	t_quadratic	q;
	float		t;

	ft_cone_coeffs(ray, cone, &q);
	if (fabsf(q.a) < 1e-6)
	{
		if (fabsf(q.b) < 1e-6)
			return (false);
		t = -q.c / q.b;
		if (t > 1e-3 && ft_check_cone_bounds(ray, cone, t))
		{
			*t_out = t;
			return (true);
		}
		return (false);
	}
	return (ft_solve_cone_quadratic(&q, ray, cone, t_out));
}
