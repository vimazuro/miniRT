/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:06:05 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/25 10:01:01 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_parse_line(t_data *data, char *line, t_counter *counter)
{
	char	**tokens;
	int		flag;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (ft_free_split(tokens), 1);
	if (ft_strcmp(tokens[0], "A") == 0)
		flag = ft_parse_ambient(data, tokens);
	else if (ft_strcmp(tokens[0], "C") == 0)
		flag = ft_parse_camera(data, tokens);
	else if (ft_strcmp(tokens[0], "L") == 0)
		flag = ft_parse_light(data, tokens);
	else if (ft_strcmp(tokens[0], "sp") == 0)
		flag = ft_parse_sphere(data, tokens);
	else if (ft_strcmp(tokens[0], "pl") == 0)
		flag = ft_parse_plane(data, tokens);
	else if (ft_strcmp(tokens[0], "cy") == 0)
		flag = ft_parse_cylinder(data, tokens);
	else if (ft_strcmp(tokens[0], "co") == 0)
		flag = ft_parse_cone(data, tokens);
	else
		flag = ft_print_error(ERROR_ELEMENTS_UNKNOWN, 0);
	ft_add_object(counter, tokens[0]);
	ft_free_split(tokens);
	return (flag);
}

void	ft_check_file_extension(char *filename, char *extension)
{
	size_t	filename_len;
	size_t	extension_len;

	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len < extension_len)
		ft_print_error(ERROR_FILE_NAME, 1);
	if (ft_strcmp(filename + filename_len - extension_len, extension) != 0)
		ft_print_error(ERROR_FILE_INVALID_EXTENSION, 1);
}

void	ft_check_file_access(char *filename)
{
	if (access(filename, F_OK) < 0)
		ft_print_error(ERROR_FILE_NOT_FOUND, 1);
	else if (access(filename, R_OK) < 0)
		ft_print_error(ERROR_FILE_NO_PERMISSION, 1);
	else if (access(filename, W_OK) < 0)
		ft_print_error(ERROR_FILE_NO_PERMISSION, 1);
}

static void	ft_counter_init(t_counter *counter)
{
	counter->ambient = 0;
	counter->camera = 0;
	counter->light = 0;
	counter->sphere = 0;
	counter->plane = 0;
	counter->cylinder = 0;
}

int	ft_parse_file(t_data *data, char *filename)
{
	int			fd;
	char		*line;
	t_counter	counter;

	ft_check_file_extension(filename, ".rt");
	ft_check_file_access(filename);
	ft_counter_init(&counter);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_print_error(ERROR_FILE_NOT_FOUND, 1);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_parse_line(data, line, &counter))
		{
			free(line);
			ft_cleanup_remaining_lines(fd);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (ft_count_objects(&counter));
}
