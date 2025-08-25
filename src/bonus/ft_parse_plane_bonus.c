/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_plane_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:10:13 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/21 17:22:43 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	ft_init_plane_base(t_plane *pl, char **tokens)
{
	int	err;

	pl->point = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (1);
	pl->normal = ft_parse_vec3(tokens[2], &err);
	if (err)
		return (1);
	pl->color = ft_parse_color(tokens[3]);
	pl->reflection = 0.0f;
	pl->has_checkerboard = false;
	pl->texture = NULL;
	pl->bump_map = NULL;
	return (0);
}

static int	ft_validate_plane_params(int count)
{
	if (count < 4 || count > 8)
	{
		ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0);
		return (1);
	}
	return (0);
}

static int	ft_parse_plane_textures(t_plane *pl, char **tokens, int count)
{
	if (count >= 7)
	{
		pl->texture = ft_load_texture(tokens[6], ERROR_PLANE_TEXTURE_LOAD);
		if (!pl->texture)
			return (1);
	}
	if (count == 8)
	{
		pl->bump_map = ft_load_texture(tokens[7], ERROR_PLANE_BUMPMAP_LOAD);
		if (!pl->bump_map)
			return (1);
	}
	return (0);
}

static int	ft_parse_plane_optional(t_plane *pl, char **tokens, int count)
{
	int	err;

	if (count >= 5)
	{
		pl->reflection = ft_atof(tokens[4], &err);
		if (err)
			return (ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0), 1);
		if (pl->reflection < 0.0f || pl->reflection > 1.0f)
			return (ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0), 1);
	}
	if (count >= 6)
	{
		if (ft_parse_checkerboard(tokens, 5, &pl->has_checkerboard))
			return (ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0), 1);
	}
	if (ft_parse_plane_textures(pl, tokens, count))
		return (1);
	return (0);
}

int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane	*pl;
	int		count;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_validate_plane_params(count))
		return (1);
	if (ft_check_coordinates(tokens[1]) || ft_check_coordinates(tokens[2]))
		return (1);
	pl = malloc(sizeof(t_plane));
	if (!pl)
		return (ft_print_error(ERROR_MALLOC, 0), 1);
	if (ft_init_plane_base(pl, tokens))
		return (free(pl), 1);
	if (ft_parse_plane_optional(pl, tokens, count))
		return (free(pl), 1);
	if (ft_check_position(pl->point, "plane")
		|| ft_check_orientation(pl->normal, "plane")
		|| ft_check_colors(&pl->color, "plane"))
		return (free(pl), 1);
	pl->normal = vec3_normalize(pl->normal);
	ft_transfer_object(data, PLANE, pl);
	return (0);
}
