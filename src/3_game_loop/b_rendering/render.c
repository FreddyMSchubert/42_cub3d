/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 16:09:24 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	render_game_scene(void)
{
	mlx_delete_image(game()->mlx, game()->game_scene);
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width, game()->mlx->height);
	do_wall_operations();

	for (int i = 0; i < game()->mlx->width; i++)
		for (int j = 0; j < game()->mlx->height; j++)
			game()->visible_walls[i][j] = false;

	mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
	print_map(game()->input_data->map, ".01");
	write(1, "\n", 1);
}
