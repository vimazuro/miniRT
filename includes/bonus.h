/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:35:49 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/14 16:52:30 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

typedef struct s_checker_data_plane
{
	t_vec3	normal;
	t_vec3	origin;
	t_vec3	ref;
	t_vec3	u;
	t_vec3	v;
	t_vec3	rel;
	float	scale;
	int		x;
	int		y;
}	t_checker_data_plane;

typedef struct s_checker_data_sphere
{
	t_vec3	rel;
	float	theta;
	float	phi;
	float	u;
	float	v;
	int		x;
	int		y;
	float	scale_u;
	float	scale_v;
}	t_checker_data_sphere;

typedef struct s_checker_data_cylinder
{
	t_vec3	rel;
	t_vec3	axis;
	t_vec3	proj;
	t_vec3	horiz;
	t_vec3	u_axis;
	t_vec3	v_axis;
	float	height;
	float	theta;
	float	u;
	float	v;
	float	scale_u;
	float	scale_v;
	float	tmp_x;
	float	tmp_y;
	int		x;
	int		y;
}	t_checker_data_cylinder;

typedef struct s_checker_data_cone
{
	t_vec3	rel;
	t_vec3	axis;
	t_vec3	proj;
	t_vec3	horiz;
	t_vec3	u_axis;
	t_vec3	v_axis;
	float	height;
	float	theta;
	float	u;
	float	current_side;
	float	base_radius;
	float	side_length;
	float	angle_rad;
	float	scale_u;
	int		x;
	int		y;
}	t_checker_data_cone;

typedef struct s_texture_data_plane
{
	t_vec3	u_vec;
	t_vec3	v_vec;
	float	texture_scale;
	float	u_coord;
	float	v_coord;
	float	u;
	float	v;
}	t_texture_data_plane;

typedef struct s_texture_data_sphere
{
	float	u;
	float	v;
}	t_texture_data_sphere;

typedef struct s_texture_data_cylinder
{
	float	u;
	float	v;
	float	scale;
	float	u_fix;
}	t_texture_data_cylinder;

typedef struct s_bump_data_plane
{
	t_vec3	u_vec;
	t_vec3	v_vec;
	float	u_coord;
	float	v_coord;
	float	u;
	float	v;
	float	texture_scale;
	float	bump_strength;
}	t_bump_data_plane;

typedef struct s_bump_data_sphere
{
	float	u;
	float	v;
	t_vec3	tangent;
	t_vec3	bitangent;
	float	bump_strength;
}	t_bump_data_sphere;

typedef struct s_bump_data_cylinder
{
	float	u;
	float	v;
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	axis;
	float	scale;
	float	u_fix;
	float	bump_strength;
}	t_bump_data_cylinder;

typedef struct s_bump_sampling
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	uint8_t	*pixel;
	uint8_t	*pixel_right;
	uint8_t	*pixel_up;
	float	height_center;
	float	height_right;
	float	height_up;
	float	du;
	float	dv;
}	t_bump_sampling;

bool			ft_obj_chboard(t_object *obj);
bool			ft_obj_texture(t_object *obj);
bool			ft_obj_bump(t_object *obj);
float			ft_get_reflection(t_object *obj);
int				ft_parse_checkerboard(char **tokens, int index,
					bool *has_checkerboard);
mlx_texture_t	*ft_load_texture(char *path_token, char *error_msg);
t_color			ft_get_checker_color(t_object *obj, t_vec3 p,
					t_color base_color);
t_color			ft_get_texture_color(t_object *obj, t_vec3 hit_point,
					t_color fallback);
t_color			ft_get_plane_texture(mlx_texture_t *texture,
					t_texture_data_plane *data);
t_color			ft_get_sphere_texture(mlx_texture_t *texture,
					t_texture_data_sphere *data);
t_color			ft_get_cylinder_texture(mlx_texture_t *texture,
					t_texture_data_cylinder *data);
t_vec3			ft_get_bump_normal(t_object *obj, t_vec3 hit_point,
					t_vec3 base_normal);
void			ft_init_checker_data_plane(t_checker_data_plane *d,
					t_object *obj, t_vec3 p);
void			ft_init_checker_data_sphere(t_checker_data_sphere *d,
					t_object *obj, t_vec3 p);
void			ft_init_checker_data_cylinder(t_checker_data_cylinder *d,
					t_object *obj, t_vec3 p);
void			ft_init_checker_data_cone(t_checker_data_cone *d,
					t_object *obj, t_vec3 p);
void			ft_init_texture_data_plane(t_plane *pl,
					t_texture_data_plane *data);
void			ft_get_uv_plane(t_plane *pl, t_texture_data_plane *data,
					t_vec3 hit_point);
void			ft_get_uv_sphere(t_sphere *sp, t_texture_data_sphere *data,
					t_vec3 hit_point);
void			ft_get_uv_cylinder(t_cylinder *cy,
					t_texture_data_cylinder *data, t_vec3 hit_point);
void			ft_get_bump_uv_plane(t_plane *pl, t_bump_data_plane *data,
					t_vec3 hit_point);
void			ft_get_bump_uv_sphere(t_sphere *sp, t_bump_data_sphere *data,
					t_vec3 hit_point);
void			ft_get_bump_uv_cylinder(t_cylinder *cy,
					t_bump_data_cylinder *data, t_vec3 hit_point);
#endif
