/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:08:22 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/29 12:05:46 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	ft_transfer_object(t_data *data, int type, void *object_data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
		ft_print_error(ERROR_MALLOC, 0);
	obj->type = type;
	obj->data = object_data;
	obj->next = data->objects;
	data->objects = obj;
}

// 1..2 no esta hecho
// el vector de orientacion no 0,0,0
int	ft_parse_plane(t_data *data, char **tokens)
{
	t_plane		*pl;
	int			count;
	t_vec3		orient_norm;

	count = 0;
	while (tokens[count])
		count++;
	if (count < 4 || count > 5)
	{
		ft_print_error(ERROR_OBJECTS_PLANE_BAD_PARAMS, 0);
		return (1);
	}
	pl = malloc(sizeof(t_plane));
	if (!pl)
		ft_print_error(ERROR_MALLOC, 0);
	pl->point = ft_parse_vec3(tokens[1]);
	pl->normal = vec3_normalize(ft_parse_vec3(tokens[2]));
	pl->color = ft_parse_color(tokens[3]);
	if (tokens[4])
		pl->reflection = ft_atof(tokens[4]);
	else
		pl->reflection = 0.0f;
	if (ft_check_position(pl->point) || ft_read_orientation(tokens[2], &orient_norm)
		|| ft_check_colors(&pl->color))
	{
		free(pl);
		return (1);
	}
	ft_transfer_object(data, PLANE, pl);
	return (0);
}

int ft_parse_sphere(t_data *data, char **tokens)
{
    t_sphere *sp;
    int       count = 0;
    t_vec3    center;
    t_color   color;
    float     diameter, reflection = 0.0f;

    while (tokens[count])
		count++;
    if (count != 4)
		{
        ft_print_error(ERROR_OBJECTS_SPHERE_BAD_PARAMS, 0);
        return 1;
    }

    /* center "x,y,z" con 3 componentes */
    if (ft_check_coordinates(tokens[1])) {
        ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
        return 1;
    }
    center = ft_parse_vec3(tokens[1]);
    if (ft_check_position(center)) {
        return 1;
    }

    /* diámetro > 0 */
    if (ft_parse_float_in_range(tokens[2], 0.0f + 1e-8f, 1e9f, &diameter)) {
        ft_print_error(ERROR_OBJECTS_SPHERE_BAD_DIAMETER, 0);
        return 1;
    }

    /* color "r,g,b" y 0..255 */
    if (ft_check_coordinates(tokens[3])) {
        ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
        return 1;
    }
    color = ft_parse_color(tokens[3]);
    if (ft_check_colors(&color)) {
        return 1;
    }

    sp = malloc(sizeof(t_sphere));
    if (!sp) ft_print_error(ERROR_MALLOC, 0);

    sp->center     = center;
    sp->diameter   = diameter;
    sp->color      = color;
    sp->reflection = reflection;

    ft_transfer_object(data, SPHERE, sp);
    return 0;
}

// 1...2
// el vector de orientacion no 0,0,0
// diametro altura > 0int	ft_parse_cylinder(t_data *data, char **tokens)
int	ft_parse_cylinder(t_data *data, char **tokens)
{
	t_cylinder	*cy;
	int			count;

	count = 0;
	while (tokens[count])
		count++;
	if (count != 6)
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_PARAMS, 0);
		return (1);
	}

	t_vec3  point;
	t_vec3  orient_norm;
	float   diameter, height, reflection = 0.0f;
	t_color color;

	/* point "x,y,z" */
	if (ft_check_coordinates(tokens[1]))
	{
		ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
		return (1);
	}
	point = ft_parse_vec3(tokens[1]);

	/* orientation "x,y,z" -> no (0,0,0) y normalizada */
	if (ft_read_orientation(tokens[2], &orient_norm))
		return (1);

	/* diámetro > 0, altura > 0 (rango abierto por arriba arbitrario) */
	if (ft_parse_float_in_range(tokens[3], 0.0f + 1e-8f, 1e9f, &diameter))
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_DIAMETER, 0);
		return (1);
	}
	if (ft_parse_float_in_range(tokens[4], 0.0f + 1e-8f, 1e9f, &height))
	{
		ft_print_error(ERROR_OBJECTS_CYLINDER_BAD_HEIGHT, 0);
		return (1);
	}

	/* color "r,g,b" y rango 0..255 */
	if (ft_check_coordinates(tokens[5]))
	{
		ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
		return (1);
	}
	color = ft_parse_color(tokens[5]);
	if (ft_check_colors(&color))
		return (1);

	/* rangos de escena */
	if (ft_check_position(point) || ft_check_orientation(orient_norm))
		return (1);

	/* si todo OK, reservamos y copiamos */
	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		ft_print_error(ERROR_MALLOC, 0);

	cy->point       = point;
	cy->orientation = orient_norm;
	cy->diameter    = diameter;
	cy->height      = height;
	cy->color       = color;
	cy->reflection  = reflection;

	ft_transfer_object(data, CYLINDER, cy);
	return (0);
}

// 1...2
// el vector de orientacion no 0,0,0
// angulo y height
int	ft_parse_cone(t_data *data, char **tokens)
{
	t_cone	*cone;
	int		count = 0;

	while (tokens[count])
		count++;
	if (count != 6)
	{
		ft_print_error(ERROR_OBJECTS_CONE_BAD_PARAMS, 0);
		return (1);
	}

	/* ---- validar y leer primero en locales ---- */
	t_vec3  point;
	t_vec3  orient_norm;
	t_color color;
	float   angle_deg, height, reflection = 0.0f;

	/* point */
	if (ft_check_coordinates(tokens[1]))
	{
		ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
		return (1);
	}
	point = ft_parse_vec3(tokens[1]);

	/* orientation: no (0,0,0) + normalizar */
	if (ft_read_orientation(tokens[2], &orient_norm))
		return (1);

	/* ángulo en grados: > 0 y < 180 (evita degenerados) */
	if (ft_parse_float_in_range(tokens[3], 0.0f + 1e-8f, 179.999f, &angle_deg))
	{
		ft_print_error(ERROR_OBJECTS_CONE_BAD_ANGLE, 0);
		return (1);
	}

	/* altura: > 0 */
	if (ft_parse_float_in_range(tokens[4], 0.0f + 1e-8f, 1e9f, &height))
	{
		ft_print_error(ERROR_OBJECTS_CONE_BAD_HEIGHT, 0);
		return (1);
	}

	/* color */
	if (ft_check_coordinates(tokens[5]))
	{
		ft_print_error(ERROR_GENERAL_BAD_COORDINATES, 0);
		return (1);
	}
	color = ft_parse_color(tokens[5]);
	if (ft_check_colors(&color))
		return (1);

	/* rangos de escena adicionales si los usas */
	if (ft_check_position(point) || ft_check_orientation(orient_norm))
		return (1);

	cone = malloc(sizeof(t_cone));
	if (!cone)
		ft_print_error(ERROR_MALLOC, 0);

	cone->point       = point;
	cone->orientation = orient_norm;
	cone->angle       = angle_deg;
	cone->height      = height;
	cone->color       = color;
	cone->reflection  = reflection;

	ft_transfer_object(data, CONE, cone);
	return (0);
}
