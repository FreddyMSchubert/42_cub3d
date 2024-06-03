/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sort_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/03 10:35:35 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	sort_and_raycast_walls(void)
{
	get_persistent_data()->raycasted_sorted_walls = get_persistent_data()->input_data->walls;
	// clear image
	mlx_image_t	*img = get_persistent_data()->game_scene;
	if (img && img->pixels && img->width > 0 && img->height > 0)
		for (int i = 0; i < (int)(img->width * img->height); i++)
			img->pixels[i] = 0;
}
