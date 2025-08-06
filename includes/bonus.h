/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:35:49 by vimazuro          #+#    #+#             */
/*   Updated: 2025/08/06 12:46:50 by vimazuro         ###   ########.fr       */
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

bool	ft_obj_chboard(t_object *obj);
float	ft_get_reflection(t_object *obj);
t_color	ft_get_checker_color(t_object *obj, t_vec3 p, t_color base_color);
void	ft_init_checker_data_plane(t_checker_data_plane *d,
			t_object *obj, t_vec3 p);
void	ft_init_checker_data_sphere(t_checker_data_sphere *d,
			t_object *obj, t_vec3 p);
void	ft_init_cheker_data_cylinder(t_checker_data_cylinder *d,
			t_object *obj, t_vec3 p);
void	ft_init_cheker_data_cone(t_checker_data_cone *d,
			t_object *obj, t_vec3 p);
#endif
