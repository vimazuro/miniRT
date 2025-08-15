/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/14 14:29:20 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_parse_checkerboard(char **tokens, int index, bool *has_checkerboard)
{
	char	*trimmed_token;
	int		ret;

	ret = 1;
	trimmed_token = ft_strtrim(tokens[index], " \n\r\t");
	if (!trimmed_token)
		return (1);
	if (ft_strcmp(trimmed_token, "checkerboard") == 0)
	{
		*has_checkerboard = true;
		ret = 0;
	}
	else if (ft_strcmp(trimmed_token, "none") == 0)
	{
		*has_checkerboard = false;
		ret = 0;
	}
	free(trimmed_token);
	return (ret);
}

mlx_texture_t	*ft_load_texture(char *path_token, char *error_msg)
{
	char			*trimmed_path;
	mlx_texture_t	*texture;

	trimmed_path = ft_strtrim(path_token, " \n\r\t");
	texture = mlx_load_png(trimmed_path);
	free(trimmed_path);
	if (!texture)
		ft_print_error(error_msg, 0);
	return (texture);
}
