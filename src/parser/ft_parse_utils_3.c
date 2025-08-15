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

int ft_is_blank_line(const char *s)
{
    if (!s)
        return 1;
    while (*s)
    {
        if (*s != ' ' && *s != '\t' && *s != '\n' && *s != '\r')
            return 0; // algo NO es whitespace
        s++;
    }
    return 1; // sólo espacios/tabs/saltos de línea
}
