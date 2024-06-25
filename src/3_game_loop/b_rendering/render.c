/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 18:56:17 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	render_game_scene(int id)
{
	mlx_delete_image(player(id)->mlx, player(id)->game_scene);
	player(id)->game_scene = mlx_new_image(player(id)->mlx, player(id)->mlx->width,
		player(id)->mlx->height);
	raycast_walls(id);
	mlx_image_to_window(player(id)->mlx, player(id)->game_scene, 0, 0);
	print_map(game()->input_data->map, ".01");
	write(1, "\n", 1);
}
