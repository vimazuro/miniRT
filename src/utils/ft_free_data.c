/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:58:17 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/19 14:00:34 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_cleanup_remaining_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static void	ft_free_textures(void *obj_data, int type,
	mlx_texture_t *tex, mlx_texture_t *bump)
{
	if (tex)
		mlx_delete_texture(tex);
	if (bump)
		mlx_delete_texture(bump);
	if (!obj_data)
		return ;
	if (type == SPHERE || type == PLANE || type == CYLINDER)
		free(obj_data);
}

static void	ft_free_object_data(t_object *obj)
{
	t_sphere	*sp;
	t_plane		*pl;
	t_cylinder	*cy;

	if (!obj || !obj->data)
		return ;
	if (obj->type == SPHERE)
	{
		sp = (t_sphere *)obj->data;
		ft_free_textures(sp, SPHERE, sp->texture, sp->bump_map);
	}
	else if (obj->type == PLANE)
	{
		pl = (t_plane *)obj->data;
		ft_free_textures(pl, PLANE, pl->texture, pl->bump_map);
	}
	else if (obj->type == CYLINDER)
	{
		cy = (t_cylinder *)obj->data;
		ft_free_textures(cy, CYLINDER, cy->texture, cy->bump_map);
	}
	else if (obj->type == CONE)
		free((t_cone *)obj->data);
}

void	ft_free_data(t_data *data)
{
	t_light		*tmp_light;
	t_object	*tmp_obj;
	t_light		*light;
	t_object	*obj;

	if (!data)
		return ;
	light = data->lights;
	while (light)
	{
		tmp_light = light->next;
		free(light);
		light = tmp_light;
	}
	data->lights = NULL;
	obj = data->objects;
	while (obj)
	{
		tmp_obj = obj->next;
		ft_free_object_data(obj);
		free(obj);
		obj = tmp_obj;
	}
	data->objects = NULL;
}
