/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:47:45 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/29 14:47:51 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// float simple: [+-]? [digits] (.[digits])?
int ft_is_float(const char *s)
{
    int i = 0, digits = 0;

    if (!s || !*s)
        return 0;
    if (s[i] == '+' || s[i] == '-')
        i++;

    while (s[i] && s[i] >= '0' && s[i] <= '9')
    {
        digits = 1;
        i++;
    }

    if (s[i] == '.')
    {
        int after = 0;
        i++;
        while (s[i] && s[i] >= '0' && s[i] <= '9')
        {
            after = 1;
            i++;
        }
        if (!digits && !after)
        return 0; // "." solo no vale
    }
    else if (!digits)
        return 0;

    // no admitimos basura al final
    return s[i] == '\0';
}

int ft_parse_float_in_range(const char *s, float min, float max, float *diameter)
{
    if (!ft_is_float(s))
        return 1;
    // Usa tu ft_atof (o atof) para convertir
    float val = ft_atof((char*)s);
    if (val < min || val > max)
        return 1;
    if (diameter)
        *diameter = val;
    return 0;
}

static int ft_read_vec3(const char *s, t_vec3 *out)
{
    if (ft_check_coordinates((char*)s)) // ya valida que hay 3 componentes
        return 1;
    if (out) *out = ft_parse_vec3((char*)s);
    return 0;
}

static int ft_is_zero_vec3(t_vec3 v)
{
    const float eps = 1e-6f;
    return (fabsf(v.x) < eps && fabsf(v.y) < eps && fabsf(v.z) < eps);
}

int ft_read_orientation(const char *s, t_vec3 *out_norm)
{
    t_vec3 raw;
    if (ft_read_vec3(s, &raw))
    {
        ft_print_error(ERROR_CAMERA_BAD_ORIENTATION, 0);
        return 1;
    }
    if (ft_is_zero_vec3(raw))
    {
        ft_print_error(ERROR_CAMERA_BAD_ORIENTATION, 0);
        return 1;
    }
    if (out_norm)
        *out_norm = vec3_normalize(raw);
    return 0;
}
