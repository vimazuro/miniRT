/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:24:52 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/23 15:33:56 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "parser.h"

# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>

# define WINDOW_H 1000
# define WINDOW_W 1500

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_cam_basis
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;
	float	aspect_ratio;
	float	scale;
}	t_cam_basis;

int			main(int argc, char **argv);
bool		ft_intersect_plane(t_ray ray, t_plane plane, float *t_out);
bool		ft_hit_object(t_ray ray, t_object *obj, float *t_out,
				t_color *color_out);
int			ft_print_error(char *text, int should_exit);
void		ft_callback_key(mlx_key_data_t keydata, void *param);
void		ft_callback_close(void *param);
void		ft_free_data(t_data *data);
void		ft_render_scene(t_data *data);
float		vec3_lenght(t_vec3 v);
float		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3(float x, float y, float z);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_normalize(t_vec3 v);
t_vec3		vec3_scale(t_vec3 v, float scalar);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
t_cam_basis	ft_camera_basis(t_camera camera);
t_ray		ft_generate_ray(t_camera cam, t_cam_basis basis, int x, int y);

#endif
