/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_checker_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:19:34 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/05 10:44:24 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_color	ft_get_plane_checker(t_object *obj, t_vec3 p,
	t_color base_color)
{
	t_checker_data_plane	pl;

	ft_init_checker_data_plane(&pl, obj, p);
	if ((pl.x + pl.y) % 2 == 0)
		return (base_color);
	else
		return ((t_color){0, 0, 0, 255});
}

static t_color	ft_get_sphere_checker(t_object *obj, t_vec3 p,
	t_color base_color)
{
	t_checker_data_sphere	sp;

	ft_init_checker_data_sphere(&sp, obj, p);
	if ((sp.x + sp.y) % 2 == 0)
		return (base_color);
	else
		return ((t_color){0, 0, 0, 255});
}

static t_color	ft_get_cylinder_checker(t_object *obj, t_vec3 p,
	t_color base_color)
{
	t_checker_data_cylinder	cy;

	ft_init_cheker_data_cylinder(&cy, obj, p);
	if ((cy.x + cy.y) % 2 == 0)
		return (base_color);
	else
		return ((t_color){0, 0, 0, 255});
}

static t_color	ft_get_cone_checker(t_object *obj, t_vec3 p,
	t_color base_color)
{
	t_checker_data_cone	cone;

	ft_init_cheker_data_cone(&cone, obj, p);
	if ((cone.x + cone.y) % 2 == 0)
		return (base_color);
	else
		return ((t_color){0, 0, 0, 255});
}

t_color	ft_get_checker_color(t_object *obj, t_vec3 p, t_color base_color)
{
	if (obj->type == PLANE)
		return (ft_get_plane_checker(obj, p, base_color));
	else if (obj->type == SPHERE)
		return (ft_get_sphere_checker(obj, p, base_color));
	else if (obj->type == CYLINDER)
		return (ft_get_cylinder_checker(obj, p, base_color));
	else if (obj->type == CONE)
		return (ft_get_cone_checker(obj, p, base_color));
	return (base_color);
}
