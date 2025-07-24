/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 13:54:29 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/24 11:31:54 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	ft_print_error(char *text, int should_exit)
{
	ft_putstr_fd(text, 2);
	if (should_exit)
		exit(EXIT_FAILURE);
	return (1);
}
