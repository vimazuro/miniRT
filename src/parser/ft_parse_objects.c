/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/21 15:48:13 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_plane	*ft_init_plane(char **tokens)
{
	t_plane	*pl;
	int		count;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 4)
		return (ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0), NULL);
	if (ft_check_coordinates(tokens[1]) || ft_check_coordinates(tokens[2]))
		return (NULL);
	pl = ft_calloc(1, sizeof(t_plane));
	if (!pl)
		return (ft_print_error(ERROR_MALLOC, 0), NULL);
	return (pl);
}

int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;
	int			err;

	pl = ft_init_plane(tokens);
	if (!pl)
		return (1);
	pl->point = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (free(pl), 1);
	pl->normal = ft_parse_vec3(tokens[2], &err);
	if (err)
		return (free(pl), 1);
	pl->color = ft_parse_color(tokens[3]);
	pl->reflection = 0.0f;
	pl->has_checkerboard = false;
	pl->texture = NULL;
	pl->bump_map = NULL;
	if (ft_check_position(pl->point, "plane")
		|| ft_check_orientation(pl->normal, "plane")
		|| ft_check_colors(&pl->color, "plane"))
		return (free(pl), 1);
	pl->normal = vec3_normalize(pl->normal);
	ft_transfer_object(data, PLANE, pl);
	return (0);
}

static t_sphere	*ft_init_sphere(char **tokens)
{
	t_sphere	*sp;
	int			count;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 4)
		return (ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0), NULL);
	if (ft_check_coordinates(tokens[1]))
		return (NULL);
	sp = ft_calloc(1, sizeof(t_sphere));
	if (!sp)
		return (ft_print_error(ERROR_MALLOC, 0), NULL);
	return (sp);
}

static int	ft_parse_sphere_diameter(t_sphere *sp, char *token)
{
	int	err;

	sp->diameter = ft_atof(token, &err);
	if (err)
	{
		ft_print_error(ERROR_GENERAL_BAD_FLOAT, 0);
		free(sp);
		return (1);
	}
	if (sp->diameter <= 0)
	{
		ft_print_error(ERROR_SPHERE_BAD_DIAMETER, 0);
		free(sp);
		return (1);
	}
	return (0);
}

int	ft_parse_sphere(t_data *data, char **tokens)
{
	t_sphere	*sp;
	int			err;

	sp = ft_init_sphere(tokens);
	if (!sp)
		return (1);
	sp->center = ft_parse_vec3(tokens[1], &err);
	if (err)
		return (free(sp), 1);
	if (ft_parse_sphere_diameter(sp, tokens[2]))
		return (1);
	sp->color = ft_parse_color(tokens[3]);
	sp->reflection = 0.0f;
	sp->has_checkerboard = false;
	sp->texture = NULL;
	sp->bump_map = NULL;
	if (ft_check_position(sp->center, "sphere")
		|| ft_check_colors(&sp->color, "sphere"))
		return (free(sp), 1);
	ft_transfer_object(data, SPHERE, sp);
	return (0);
}
