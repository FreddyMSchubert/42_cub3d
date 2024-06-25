/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:50:17 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 15:14:31 by freddy           ###   ########.fr       */
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
}
