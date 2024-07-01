/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 13:00:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	render_game_scene(void)
{
	ft_memset(game()->game_scene->pixels, 0, game()->mlx->width
		* game()->mlx->height * 4);
	raycast_walls();
	draw_crosshair();
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
