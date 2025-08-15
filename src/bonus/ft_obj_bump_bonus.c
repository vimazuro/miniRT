/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_bump_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:08:12 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 14:51:53 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_obj_bump(t_object *obj)
{
	if (!obj)
		return (false);
	if (obj->type == PLANE && ((t_plane *)obj->data)->bump_map)
		return (true);
	if (obj->type == SPHERE && ((t_sphere *)obj->data)->bump_map)
		return (true);
	if (obj->type == CYLINDER && ((t_cylinder *)obj->data)->bump_map)
		return (true);
	return (false);
}
