/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:50:17 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 11:05:13 by jkauker          ###   ########.fr       */
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
		printf("mouse moved, set dirty to true!\n");
	turn((current_mouse_x - game()->prev_mouse_x) * MOUSE_SENSITIVITY);
	game()->prev_mouse_x = current_mouse_x;
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	(void)param;
	(void)xdelta;
	if (ydelta != 0)
	{
		if (ydelta > 0)
			game()->minimap_size += 1;
		else
			game()->minimap_size -= 1;
		if (game()->minimap_size < 2)
			game()->minimap_size = 2;
		if (game()->minimap_size > 6)
			game()->minimap_size = 6;
	}
}
