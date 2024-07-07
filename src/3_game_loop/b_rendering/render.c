/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/07/07 16:26:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	render_game_scene(void)
{
	ft_memset(game()->game_scene->pixels, 0, game()->mlx->width
		* game()->mlx->height * 4);
	raycast_walls();
	draw_crosshair();
	draw_elements_overview();
}

static inline void	render_hud(void)
{
	ft_memset(game()->hud->pixels, 0, game()->hud->width
		* game()->hud->height * 4);
	if (game()->input_data->show_minimap)
		hud_draw_minimap();
}

void	render(void)
{
	timing(TIMING_MODE_START, TIMING_TYPE_RENDERING);
	timing(TIMING_MODE_START, TIMING_TYPE_WORLD_RENDERING);
	render_game_scene();
	timing(TIMING_MODE_STOP, TIMING_TYPE_WORLD_RENDERING);
	timing(TIMING_MODE_START, TIMING_TYPE_HUD_RENDERING);
	draw_inventory();
	render_hud();
	timing(TIMING_MODE_STOP, TIMING_TYPE_HUD_RENDERING);
	timing(TIMING_MODE_STOP, TIMING_TYPE_RENDERING);
}
