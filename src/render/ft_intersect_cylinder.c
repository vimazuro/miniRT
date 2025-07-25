/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_username <your_username@student.42.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:00:00 by your_username    #+#    #+#             */
/*   Updated: 2025/07/24 12:00:00 by your_username   ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
1) Set up a quadratic equation for the infinite cylinder.
2) Solve it for intersection points along the ray.
3) Check if those points are within the finite height of the cylinder.
4) Return the closest valid intersection.
*/

#include "../../includes/minirt.h"

static bool	ft_check_cylinder_caps(t_ray ray, t_cylinder cylinder, float t)
{
	t_vec3	hit_point;
	t_vec3	to_hit;
	float	projection;

	hit_point = vec3_add(ray.origin, vec3_scale(ray.direction, t));
	to_hit = vec3_sub(hit_point, cylinder.point);
	projection = vec3_dot(to_hit, cylinder.orientation);
	
	return (projection >= 0 && projection <= cylinder.height);
}

static void	ft_cylinder_coeffs(t_ray ray, t_cylinder cylinder, t_quadratic *q)
{
	t_vec3	oc;
	t_vec3	d_perp;
	t_vec3	oc_perp;
	float	radius;

	oc = vec3_sub(ray.origin, cylinder.point);
	radius = cylinder.diameter / 2.0f;
	d_perp = vec3_sub(ray.direction, 
		vec3_scale(cylinder.orientation, 
			vec3_dot(ray.direction, cylinder.orientation)));
	oc_perp = vec3_sub(oc, 
		vec3_scale(cylinder.orientation, 
			vec3_dot(oc, cylinder.orientation)));
	q->a = vec3_dot(d_perp, d_perp);
	q->b = 2.0f * vec3_dot(oc_perp, d_perp);
	q->c = vec3_dot(oc_perp, oc_perp) - (radius * radius);
}

static bool	ft_solve_cylinder_quadratic(t_quadratic *q, t_ray ray, 
	t_cylinder cylinder, float *t_out)
{
	float	sqrt_d;
	float	t1, t2;

	q->discriminant = q->b * q->b - 4 * q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	sqrt_d = sqrtf(q->discriminant);
	t1 = (-q->b - sqrt_d) / (2.0f * q->a);
	t2 = (-q->b + sqrt_d) / (2.0f * q->a);
	
	if (t1 > 0 && ft_check_cylinder_caps(ray, cylinder, t1))
	{
		*t_out = t1;
		return (true);
	}
	if (t2 > 0 && ft_check_cylinder_caps(ray, cylinder, t2))
	{
		*t_out = t2;
		return (true);
	}
	return (false);
}

bool	ft_intersect_cylinder(t_ray ray, t_cylinder cylinder, float *t_out)
{
	t_quadratic	q;
	
	ft_cylinder_coeffs(ray, cylinder, &q);
	if (fabsf(q.a) < 1e-6)
		return (false);
	
	return (ft_solve_cylinder_quadratic(&q, ray, cylinder, t_out));
}