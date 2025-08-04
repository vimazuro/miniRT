/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_reflection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:59:58 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/04 16:49:05 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float	ft_get_reflection(t_object *obj)
{
	if (obj->type == SPHERE)
		return (((t_sphere *)obj->data)->reflection);
	if (obj->type == PLANE)
		return (((t_plane *)obj->data)->reflection);
	if (obj->type == CYLINDER)
		return (((t_cylinder *)obj->data)->reflection);
	if (obj->type == CONE)
		return (((t_cone *)obj->data)->reflection);
	return (0.0f);
}
