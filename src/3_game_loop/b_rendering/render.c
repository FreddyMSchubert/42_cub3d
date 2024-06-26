/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 12:20:13 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	render_game_scene(void)
{
	if (game()->game_scene)
		mlx_delete_image(game()->mlx, game()->game_scene);
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	if (!game()->game_scene)
		cub_exit("Failed to create game scene image.", -1);
	do_wall_operations();
	draw_crosshair();
	// hud_toogle_worldmap(false);
	mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
}

static inline void	render_hud(void)
{
	if (game()->hud)
		mlx_delete_image(game()->mlx, game()->hud);
	game()->hud = mlx_new_image(game()->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (!game()->hud)
		cub_exit("Failed to create HUD image.", -1);
	hud_draw_minimap();
	mlx_image_to_window(game()->mlx, game()->hud, MINIMAP_LEFT_OFFSET,
		MINIMAP_TOP_OFFSET);
}

void	render(void)
{
	render_game_scene();
	render_hud();
}
