/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cone_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:15:21 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/15 14:51:56 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_init_cone_base(t_cone *cone, char **tokens)
{
	cone->point = ft_parse_vec3(tokens[1]);
	cone->orientation = vec3_normalize(ft_parse_vec3(tokens[2]));
	cone->angle = ft_atof(tokens[3]);
	cone->height = ft_atof(tokens[4]);
	cone->color = ft_parse_color(tokens[5]);
	cone->reflection = 0.0f;
	cone->has_checkerboard = false;
}

static int	ft_validate_cone_params(int count)
{
	if (count < 6 || count > 8)
	{
		ft_print_error(ERROR_OBJECTS_CONE_BAD_PARAMS, 0);
		return (1);
	}
	return (0);
}

static int	ft_parse_cone_optional(t_cone *cone, char **tokens, int count)
{
	if (count >= 7)
	{
		cone->reflection = ft_atof(tokens[6]);
		if (cone->reflection < 0.0f || cone->reflection > 1.0f)
		{
			ft_print_error(ERROR_OBJECTS_CONE_BAD_PARAMS, 0);
			return (1);
		}
	}
	if (count == 8)
	{
		if (ft_parse_checkerboard(tokens, 7, &cone->has_checkerboard))
		{
			ft_print_error(ERROR_OBJECTS_CONE_BAD_PARAMS, 0);
			return (1);
		}
	}
	return (0);
}

int	ft_parse_cone(t_data *data, char **tokens)
{
	t_cone	*co;
	int		count;

	count = 0;
	while (tokens[count])
		count++;
	if (ft_validate_cone_params(count))
		return (1);
	co = malloc(sizeof(t_cone));
	if (!co)
		ft_print_error(ERROR_MALLOC, 0);
	ft_init_cone_base(co, tokens);
	if (ft_parse_cone_optional(co, tokens, count))
	{
		free(co);
		return (1);
	}
	if (ft_check_position(co->point) || ft_check_orientation(co->orientation)
		|| co->angle <= 0 || co->height <= 0 || ft_check_colors(&co->color))
	{
		free(co);
		return (1);
	}
	ft_transfer_object(data, CONE, co);
	return (0);
}
