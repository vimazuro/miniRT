/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sphere_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:12:08 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/21 17:04:33 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	ft_init_sphere_base(t_sphere *sp, char **tokens)
{
	int	err;

	sp->center = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (1);
	sp->diameter = ft_atof(tokens[2], &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		return (1);
	}
	if (sp->diameter <= 0)
	{
		ft_print_error(ERROR_SPHERE_BAD_DIAMETER, 0);
		return (1);
	}
	sp->color = ft_parse_color(tokens[3]);
	sp->reflection = 0.0f;
	sp->has_checkerboard = false;
	sp->texture = NULL;
	sp->bump_map = NULL;
	return (0);
}

static int	ft_validate_sphere_params(int count)
{
	if (count < 4 || count > 8)
	{
		ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0);
		return (1);
	}
	return (0);
}

static int	ft_parse_sphere_textures(t_sphere *sp, char **tokens, int count)
{
	if (count >= 7)
	{
		sp->texture = ft_load_texture(tokens[6], ERROR_SPHERE_TEXTURE_LOAD);
		if (!sp->texture)
			return (1);
	}
	if (count == 8)
	{
		sp->bump_map = ft_load_texture(tokens[7], ERROR_SPHERE_BUMPMAP_LOAD);
		if (!sp->bump_map)
			return (1);
	}
	return (0);
}

static int	ft_parse_sphere_optional(t_sphere *sp, char **tokens, int count)
{
	int	err;

	if (count >= 5)
	{
		sp->reflection = ft_atof(tokens[4], &err);
		if (err)
			return (ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0), 1);
		if (sp->reflection < 0.0f || sp->reflection > 1.0f)
			return (ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0), 1);
	}
	if (count >= 6)
	{
		if (ft_parse_checkerboard(tokens, 5, &sp->has_checkerboard))
			return (ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0), 1);
	}
	if (ft_parse_sphere_textures(sp, tokens, count))
		return (1);
	return (0);
}

int	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;
	int			count;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_validate_sphere_params(count))
		return (1);
	if (ft_check_coordinates(tokens[1]))
		return (1);
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (ft_print_error(ERROR_MALLOC, 0), 1);
	if (ft_init_sphere_base(sp, tokens))
		return (free(sp), 1);
	if (ft_parse_sphere_optional(sp, tokens, count))
		return (free(sp), 1);
	if (ft_check_position(sp->center, "sphere")
		|| sp->diameter <= 0
		|| ft_check_colors(&sp->color, "sphere"))
		return (free(sp), 1);
	ft_transfer_object(data, SPHERE, sp);
	return (0);
}
