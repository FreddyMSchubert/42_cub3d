/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:23:40 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/04 15:24:55 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	update_mouse_visibility(void)
{
	if (game()->mouse_free)
		mlx_set_cursor_mode(game()->mlx, MLX_MOUSE_HIDDEN);
	else
		mlx_set_cursor_mode(game()->mlx, MLX_MOUSE_NORMAL);
}
