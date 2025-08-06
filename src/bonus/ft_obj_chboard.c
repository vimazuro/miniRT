/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_chboard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:12:44 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/05 10:26:29 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_obj_chboard(t_object *obj)
{
	if (!obj)
		return (false);
	if (obj->type == PLANE)
		return (((t_plane *)obj->data)->has_checkerboard);
	else if (obj->type == SPHERE)
		return (((t_sphere *)obj->data)->has_checkerboard);
	else if (obj->type == CYLINDER)
		return (((t_cylinder *)obj->data)->has_checkerboard);
	else if (obj->type == CONE)
		return (((t_cone *)obj->data)->has_checkerboard);
	return (false);
}
