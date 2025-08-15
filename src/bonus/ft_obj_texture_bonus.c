/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_texture_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:33:25 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/13 11:55:43 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	ft_obj_texture(t_object *obj)
{
	if (!obj)
		return (false);
	if (obj->type == PLANE && ((t_plane *)obj->data)->texture)
		return (true);
	if (obj->type == SPHERE && ((t_sphere *)obj->data)->texture)
		return (true);
	if (obj->type == CYLINDER && ((t_cylinder *)obj->data)->texture)
		return (true);
	return (false);
}
