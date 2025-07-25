/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 13:46:06 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/22 15:26:40 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_sphere_coeffs(t_ray ray, t_sphere sphere, t_quadratic *q)
{
	t_vec3	oc;
	float	radius;

	oc = vec3_sub(ray.origin, sphere.center);
	radius = sphere.diameter / 2.0f;
	q->a = vec3_dot(ray.direction, ray.direction);
	q->b = 2.0f * vec3_dot(oc, ray.direction);
	q->c = vec3_dot(oc, oc) - (radius * radius);
}

static bool	ft_solve_quadratic(t_quadratic *q, float *t_out)
{
	float	sqrt_d;

	q->discriminant = q->b * q->b - 4 * q->a * q->c;
	if (q->discriminant < 0)
		return (false);
	sqrt_d = sqrtf(q->discriminant);
	q->t1 = (-q->b - sqrt_d) / (2.0f * q->a);
	q->t2 = (-q->b + sqrt_d) / (2.0f * q->a);
	if (q->t1 > 0 && q->t2 > 0)
		*t_out = fminf(q->t1, q->t2);
	else if (q->t1 > 0)
		*t_out = q->t1;
	else if (q->t2 > 0)
		*t_out = q->t2;
	else
		return (false);
	return (true);
}

bool	ft_intersect_sphere(t_ray ray, t_sphere sphere, float *t_out)
{
	t_quadratic	q;
	bool		detected;

	ft_sphere_coeffs(ray, sphere, &q);
	detected = ft_solve_quadratic(&q, t_out);
	return (detected);
}
