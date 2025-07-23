/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:06:05 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:59:13 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_parse_line(t_data *data, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return ;
	if (ft_strcmp(tokens[0], "A") == 0)
		ft_parse_ambient(data, tokens);
	else if (ft_strcmp(tokens[0], "C") == 0)
		ft_parse_camera(data, tokens);
	else if (ft_strcmp(tokens[0], "L") == 0)
		ft_parse_light(data, tokens);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		ft_parse_sphere(data, tokens);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		ft_parse_plane(data, tokens);
	else
		ft_print_error("unknown element\n");
	ft_free_split(tokens);
}

void	ft_parse_file(t_data *data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_print_error("can't open file\n");
	line = get_next_line(fd);
	while (line)
	{
		ft_parse_line(data, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
