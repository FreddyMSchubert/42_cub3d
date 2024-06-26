/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/26 12:18:04 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_crosshair(void)
{
	int	size;

	size = 3;
	draw_square(game()->game_scene->width / 2, game()->game_scene->height / 2,
		size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2 + size, game()->game_scene->height
		/ 2, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2, game()->game_scene->height
		/ 2 + size, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2 - size,
		game()->game_scene->height / 2, size, rgba_to_int(255, 255, 255, 255));
	draw_square(game()->game_scene->width / 2, game()->game_scene->height
		/ 2 - size, size, rgba_to_int(255, 255, 255, 255));
}
