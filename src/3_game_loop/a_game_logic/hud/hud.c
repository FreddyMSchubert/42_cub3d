/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/25 20:09:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	draw_crosshair(int id)
{
	int	size;

	size = 3;
	draw_square(player(id)->game_scene->width / 2, player(id)->game_scene->height / 2,
		size, rgba_to_int(255, 255, 255, 255), id);
	draw_square(player(id)->game_scene->width / 2 + size, player(id)->game_scene->height
		/ 2, size, rgba_to_int(255, 255, 255, 255), id);
	draw_square(player(id)->game_scene->width / 2, player(id)->game_scene->height
		/ 2 + size, size, rgba_to_int(255, 255, 255, 255), id);
	draw_square(player(id)->game_scene->width / 2 - size,
		player(id)->game_scene->height / 2, size, rgba_to_int(255, 255, 255, 255), id);
	draw_square(player(id)->game_scene->width / 2, player(id)->game_scene->height
		/ 2 - size, size, rgba_to_int(255, 255, 255, 255), id);
}

void	hud_draw(int id)
{
	if (player(id)->hud)
	{
		mlx_delete_image(player(id)->mlx, player(id)->hud);
		player(id)->hud = mlx_new_image(player(id)->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
		if (!player(id)->hud)
			cub_exit("Failed to create HUD image.", -1);
		hud_draw_minimap(id);
		mlx_image_to_window(player(id)->mlx, player(id)->hud, MINIMAP_LEFT_OFFSET,
			MINIMAP_TOP_OFFSET);
	}
	draw_crosshair(id);
	hud_toogle_worldmap(false, id);
}
