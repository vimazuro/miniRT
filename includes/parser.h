/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:05:16 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/24 10:04:53 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

# define ERROR_ARGUMENTS_AMOUNT "Error\nbad arguments (try ./miniRT <path_to_file.rt>\n"
# define ERROR_GENERAL_BAD_COORDINATES "Error\nbad coordinates (try <x>,<y>,<z>)\n"
# define ERROR_FILE_NOT_FOUND "Error\nfile: file not found\n"
# define ERROR_FILE_NAME "Error\nfile: invalid file name\n"
# define ERROR_FILE_INVALID_EXTENSION "Error\nfile: invalid extension\n"
# define ERROR_FILE_EMPTY "Error\nfile: empty file\n"
# define ERROR_FILE_NO_PERMISSION "Error\nfile: no permission\n"
# define ERROR_ELEMENTS_UNKNOWN "Error\nunknown element\n"
# define ERROR_MLX_INIT "Error\nmlx_init failed\n"
# define ERROR_MLX_NEW_IMAGE "Error\nmlx_new_image failed\n"
# define ERROR_MLX_IMAGE_TO_WINDOW "Error:\nmlx_image_to_window failed\n"
# define ERROR_MALLOC "Error:\nmalloc failed\n"
# define ERROR_AMBIENT_BAD_COUNT "Error:\nambient light: bad count\n"
# define ERROR_AMBIENT_BAD_PARAMS "Error:\nambient light: bad parameters\n"
# define ERROR_AMBIENT_BAD_RATIO "Error:\nambient light: bad ratio\n"
# define ERROR_AMBIENT_BAD_COLORS "Error:\nambient light: bad colors\n"
# define ERROR_CAMERA_BAD_COUNT "Error:\ncamera: bad count\n"
# define ERROR_CAMERA_BAD_PARAMS "Error:\ncamera: bad parameters\n"
# define ERROR_CAMERA_BAD_POSITION "Error:\ncamera: bad position\n"
# define ERROR_CAMERA_BAD_ORIENTATION "Error:\ncamera: bad orientation\n"
# define ERROR_CAMERA_BAD_FOV "Error:\ncamera: bad field of view\n"
# define ERROR_LIGHT_BAD_COUNT "Error:\nlight: bad count\n"
# define ERROR_LIGHT_BAD_PARAMS "Error:\nlight: bad parameters\n"
# define ERROR_LIGHT_BAD_POSITION "Error:\nlight: bad position\n"
# define ERROR_LIGHT_BAD_BRIGHTNESS "Error:\nlight: bad brightness\n"

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

typedef struct s_cylinder
{
	t_vec3	point;
	t_vec3	orientation;
	float	diameter;
	float	height;
	t_color	color;
}	t_cylinder;

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

typedef struct s_counter
{
	int	ambient;
	int	camera;
	int	light;
	int	sphere;
	int	plane;
	int	cylinder;
}	t_counter;

int		ft_parse_file(t_data *data, char *filename);
int		ft_parse_line(t_data *data, char *line, t_counter *counter);
int		ft_parse_ambient(t_data *data, char **tokens);
int		ft_parse_camera(t_data *data, char **tokens);
int		ft_parse_light(t_data *data, char **tokens);
int		ft_parse_sphere(t_data *data, char **tokens);
int		ft_parse_cylinder(t_data *data, char **tokens);
int		ft_parse_plane(t_data *data, char **tokens);
int		ft_count_objects(t_counter *counter);
int		ft_check_ratio(float ratio);
int		ft_check_position(t_vec3 position);
int		ft_check_orientation(t_vec3 orientation);
int		ft_check_coordinates(char *coords);
void	ft_check_file_extension(char *filename, char *extension);
void	ft_check_file_access(char *filename);
void	ft_add_object(t_counter *counter, char *type);
void	ft_free_split(char **ptr);
t_color	ft_parse_color(char *str);
t_vec3	ft_parse_vec3(char *str);

#endif
