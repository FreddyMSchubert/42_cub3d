/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 15:25:33 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	render_game_scene(void)
{
	// if (game()->game_scene)
	// 	mlx_delete_image(game()->mlx, game()->game_scene);
	// game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width,
	// 	game()->mlx->height);
	// if (!game()->game_scene)
	// 	cub_exit("Failed to create game scene image.", -1);
	ft_memset(game()->game_scene->pixels, 0, game()->mlx->width
		* game()->mlx->height * 4);
	do_wall_operations();
	draw_crosshair();
	// hud_toogle_worldmap(false);
	// mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
}

static inline void	render_hud(void)
{
	ft_memset(game()->hud->pixels, 0, game()->hud->width
		* game()->hud->height * 4);
	hud_draw_minimap();
}

void	render(void)
{
	render_game_scene();
	draw_inventory();
	render_hud();
}
