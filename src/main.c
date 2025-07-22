/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimazuro <vimazuro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 12:33:10 by vimazuro          #+#    #+#             */
/*   Updated: 2025/07/21 16:28:58 by vimazuro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc < 2)
		ft_print_error("enter .rf file\n");
	ft_parse_file(&data, argv[1]);
	data.mlx = mlx_init(WINDOW_W, WINDOW_H, argv[1], false);
	if (!data.mlx)
		ft_print_error("error: mlx_init\n");
	data.img = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	if (!data.img)
		ft_print_error("error: mlx_new_image\n");
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) < 0)
		ft_print_error("error: mlx_image_to_window\n");
	ft_render_scene(&data);
	mlx_key_hook(data.mlx, ft_callback_key, &data);
	mlx_close_hook(data.mlx, ft_callback_close, &data);
	mlx_loop(data.mlx);
	return (0);
}
