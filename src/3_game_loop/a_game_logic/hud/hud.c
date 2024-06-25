/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/25 13:32:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	draw_crosshair(void)
{
	int	size;

	size = 3;
	draw_square(game()->game_scene->width / 2, game()->game_scene->height / 2,
		size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2 + size, game()->game_scene->height
		/ 2, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2, game()->game_scene->height
		/ 2 + size, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2 - size,
		game()->game_scene->height / 2, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2, game()->game_scene->height
		/ 2 - size, size, rgba_to_int(255, 255, 255, 255));
}

void	hud_draw(void)
{
	if (game()->hud)
	{
		mlx_delete_image(game()->mlx, game()->hud);
		game()->hud = mlx_new_image(game()->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		if (!game()->hud)
			cub_exit_error("Failed to create HUD image.");
		hud_draw_minimap();
		mlx_image_to_window(game()->mlx, game()->hud, MINIMAP_LEFT_OFFSET,
			MINIMAP_TOP_OFFSET);
	}
	draw_crosshair();
}
