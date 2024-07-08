/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:45:16 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/08 12:37:23 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	set_background(void);

static inline void	reset_hud_amount_text(void)
{
	if (player()->inv.text_amount_key)
		mlx_delete_image(game()->mlx, player()->inv.text_amount_key);
	if (player()->inv.text_amount_water)
		mlx_delete_image(game()->mlx, player()->inv.text_amount_water);
	if (player()->inv.text_amount_fire)
		mlx_delete_image(game()->mlx, player()->inv.text_amount_fire);
	if (player()->inv.text_amount_earth)
		mlx_delete_image(game()->mlx, player()->inv.text_amount_earth);
	if (player()->inv.text_amount_air)
		mlx_delete_image(game()->mlx, player()->inv.text_amount_air);
	player()->inv.text_amount_key = NULL;
	player()->inv.text_amount_water = NULL;
	player()->inv.text_amount_fire = NULL;
	player()->inv.text_amount_earth = NULL;
	player()->inv.text_amount_air = NULL;
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	(void)param;
	game()->mlx->width = width;
	game()->mlx->height = height;
	if (game()->background)
		mlx_delete_image(game()->mlx, game()->background);
	if (game()->game_scene)
		mlx_delete_image(game()->mlx, game()->game_scene);
	if (game()->hud)
		mlx_delete_image(game()->mlx, game()->hud);
	set_background();
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	if (game()->game_scene)
		cub_exit("Failed to create game scene image", -1);
	mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
	game()->hud = mlx_new_image(game()->mlx, game()->mlx->width,
		game()->mlx->height);
	if (game()->hud)
		cub_exit("Failed to create hud image", -1);
	mlx_image_to_window(game()->mlx, game()->hud, 0, 0);
	reset_hud_amount_text();
	render();
}
