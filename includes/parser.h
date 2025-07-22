/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:05:16 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:44:57 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	uint32_t	pixel_color;
}	t_color;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ambient
{
	float	lighting;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3			position;
	float			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
}	t_object_type;

typedef struct s_sphere
{
	t_vec3	center;
	float	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_object
{
	t_object_type	type;
	void			*data;
	struct s_object	*next;
}	t_object;

typedef struct s_data
{
	mlx_t				*mlx;
	mlx_image_t			*img;
	struct s_ambient	ambient;
	struct s_camera		camera;
	struct s_light		*lights;
	struct s_object		*objects;
}	t_data;

void	ft_parse_file(t_data *data, char *filename);
void	ft_parse_line(t_data *data, char *line);
void	ft_parse_ambient(t_data *data, char **tokens);
void	ft_parse_camera(t_data *data, char **tokens);
void	ft_parse_light(t_data *data, char **tokens);
void	ft_parse_sphere(t_data *data, char **tokens);
void	ft_parse_plane(t_data *data, char **tokens);
void	ft_free_split(char **ptr);
t_color	ft_parse_color(char *str);
t_vec3	ft_parse_vec3(char *str);

#endif
