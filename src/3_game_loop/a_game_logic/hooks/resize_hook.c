/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:45:16 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/26 12:54:56 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	set_background(void);

void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	game()->mlx->width = width;
	game()->mlx->height = height;
	mlx_delete_image(game()->mlx, game()->background);
	mlx_delete_image(game()->mlx, game()->game_scene);
	mlx_delete_image(game()->mlx, game()->hud);
	write(1, "Resized\n", 8);
	set_background();
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
	game()->hud = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	mlx_image_to_window(game()->mlx, game()->hud, 0, 0);
	render();
	write(1, "called render\n", 14);
}
