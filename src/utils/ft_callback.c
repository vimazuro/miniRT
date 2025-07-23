/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_callback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 17:13:04 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:29:29 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	ft_callback_key(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		ft_free_data(data);
		mlx_terminate(data->mlx);
		exit(0);
	}
}

void	ft_callback_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	ft_free_data(data);
	mlx_terminate(data->mlx);
	exit(0);
}
