/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:25:16 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/25 11:09:47 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool ft_check_cone_bounds(t_ray ray, t_cone cone, float t)
{
	t_vec3  hit_point;
	t_vec3  to_hit;
	float   projection;
	float   radius_at_height;
	t_vec3  axis_to_hit;
	float   perp_distance;

	hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	to_hit = vec3_sub(hit_point, cone.point);
	projection = vec3_dot(to_hit, cone.orientation);
	
	if (projection < -1e-4 || projection > cone.height + 1e-4)
		return (false);
	
	radius_at_height = tanf(cone.angle * M_PI / 180.0f) * projection;
	
	if (projection < 1e-3)
		return (true);
	
	axis_to_hit = vec3_sub(to_hit, vec3_scale(cone.orientation, projection));
	perp_distance = vec3_length(axis_to_hit);
	
	return (perp_distance <= radius_at_height + 1e-4);
}

static bool ft_solve_cone_quadratic(t_quadratic *q, t_ray ray, 
	t_cone cone, float *t_out)
{
	float   sqrt_d;
	float   t1, t2;

	if (q->discriminant < 0)
		return (false);
	
	sqrt_d = sqrtf(q->discriminant);
	t1 = (-q->b - sqrt_d) / (2.0f * q->a);
	t2 = (-q->b + sqrt_d) / (2.0f * q->a);

	if (t1 > t2)
	{
		float temp = t1;
		t1 = t2;
		t2 = temp;
	}

	if (t1 > 1e-4 && ft_check_cone_bounds(ray, cone, t1))
	{
		*t_out = t1;
		return (true);
	}
	if (t2 > 1e-4 && ft_check_cone_bounds(ray, cone, t2))
	{
		*t_out = t2;
		return (true);
	}
	
	return (false);
}

static void ft_cone_coeffs(t_ray ray, t_cone cone, t_quadratic *q)
{
	t_vec3  oc;
	float   tan_theta;
	float   tan_theta_sq;
	float   d_dot_v;
	float   oc_dot_v;
	float   d_dot_d;
	float   oc_dot_d;
	float   oc_dot_oc;

	oc = vec3_sub(ray.origin, cone.point);
	tan_theta = tanf(cone.angle * M_PI / 180.0f);
	tan_theta_sq = tan_theta * tan_theta;
	
	d_dot_v = vec3_dot(ray.direction, cone.orientation);
	oc_dot_v = vec3_dot(oc, cone.orientation);
	d_dot_d = vec3_dot(ray.direction, ray.direction);
	oc_dot_d = vec3_dot(oc, ray.direction);
	oc_dot_oc = vec3_dot(oc, oc);

	q->a = d_dot_d - d_dot_v * d_dot_v * (1.0f + tan_theta_sq);
	q->b = 2.0f * (oc_dot_d - oc_dot_v * d_dot_v * (1.0f + tan_theta_sq));
	q->c = oc_dot_oc - oc_dot_v * oc_dot_v * (1.0f + tan_theta_sq);
	q->discriminant = q->b * q->b - 4.0f * q->a * q->c;
}

bool ft_intersect_cone(t_ray ray, t_cone cone, float *t_out)
{
	t_quadratic q;

	ft_cone_coeffs(ray, cone, &q);

	if (fabsf(q.a) < 1e-6)
	{
		if (fabsf(q.b) < 1e-6)
			return (false);
		
		float t = -q.c / q.b;
		if (t > 1e-6 && ft_check_cone_bounds(ray, cone, t))
		{
			*t_out = t;
			return (true);
		}
		return (false);
	}
	
	return (ft_solve_cone_quadratic(&q, ray, cone, t_out));
}