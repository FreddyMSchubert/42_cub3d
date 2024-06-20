/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 05:35:25 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	render_game_scene(void)
{
	mlx_delete_image(game()->mlx, game()->game_scene);
	game()->game_scene = mlx_new_image(game()->mlx, game()->mlx->width, game()->mlx->height);
	do_wall_operations();
	mlx_image_to_window(game()->mlx, game()->game_scene, 0, 0);
	print_map(game()->input_data->map, ".01");
}
