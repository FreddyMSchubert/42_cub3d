/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:50:17 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 15:26:30 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	handle_mouse_mv(void)
{
	int32_t	current_mouse_x;
	int32_t	current_mouse_y;

	mlx_get_mouse_pos(game()->mlx, &current_mouse_x, &current_mouse_y);
	if (current_mouse_x == game()->prev_mouse_x)
		return ;
	game()->dirty = true;
	if (MARK_DIRTY_LOGGING)
		logger(LOGGER_INFO, "Mouse moved, set dirty to true!\n");
	turn((current_mouse_x - game()->prev_mouse_x) * MOUSE_SENSITIVITY);
	game()->prev_mouse_x = current_mouse_x;

	/*
	mouse reset logic gotta be in here:
	mlx_set_mouse_pos(game()->mlx, game()->mlx->width / 2, game()->mlx->height / 2);
	*/
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	(void)param;
	(void)xdelta;
	if (ydelta != 0)
	{
		if (ydelta > 0)
			cycle_inventory(1, false);
		else
			cycle_inventory(-1, false);
	}
}

void	mouse_click_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	(void)param;
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && player()->inv.air_orbs > 0)
		shooooot(player()->transform, ORB_TYPE_AIR);
}

void	cursor_hook(double x, double y, void *param)
{
	(void)param;
	(void)x;
	(void)y;
	return ;
	// mlx_set_mouse_pos(game()->mlx, game()->mlx->width / 2, game()->mlx->height / 2);
}
