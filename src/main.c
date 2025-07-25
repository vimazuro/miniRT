/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:33:10 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/24 11:24:06 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2)
		ft_print_error(ERROR_ARGUMENTS_AMOUNT, 1);
	if (ft_parse_file(&data, argv[1]))
	{
		ft_free_data(&data);
		return (1);
	}
	data.mlx = mlx_init(WINDOW_W, WINDOW_H, argv[1], false);
	if (!data.mlx)
		ft_print_error(ERROR_MLX_INIT, 1);
	data.img = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	if (!data.img)
		ft_print_error(ERROR_MLX_NEW_IMAGE, 1);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
		ft_print_error(ERROR_MLX_IMAGE_TO_WINDOW, 1);
	ft_render_scene(&data);
	mlx_key_hook(data.mlx, ft_callback_key, &data);
	mlx_close_hook(data.mlx, ft_callback_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
