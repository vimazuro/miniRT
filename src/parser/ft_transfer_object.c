/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_transfer_object.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 12:30:42 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/14 12:30:59 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_transfer_object(t_data *data, int type, void *object_data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = type;
	obj->data = object_data;
	obj->next = data->objects;
	data->objects = obj;
}
