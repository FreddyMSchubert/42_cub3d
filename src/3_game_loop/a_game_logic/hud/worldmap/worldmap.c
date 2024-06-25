/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worldmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/25 20:05:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/cub3d.h"

int	get_opacity(int x, int y);

void	draw_worldmap_tile(t_scale ij, int size, int offset_x, int offset_y, int id)
{
	t_tile_type	***walls;
	int			draw_x;
	int			draw_y;
	int			j;
	int			i;

	i = ij.x;
	j = ij.y;
	walls = game()->input_data->map;
	draw_x = j * size + offset_x - size / 2;
	draw_y = i * size + offset_y - size / 2;
	if (*(walls[i][j]) == VOID)
		draw_square_world(draw_x, draw_y, size,
			rgba_to_int(50, 50, 50, 255), id);
	else if (*(walls[i][j]) == WALL)
		draw_square_world(draw_x, draw_y, size,
			rgba_to_int(255, 0, 0, 255), id);
	else if (*(walls[i][j]) == FLOOR)
		draw_square_world(draw_x, draw_y, size,
			rgba_to_int(0, 255, 0, 255), id);
}

static inline void	draw_worldmap(int id)
{
	t_scale		ij;
	int			size;
	int			offset_x;
	int			offset_y;

	size = 5;
	offset_x = 10;
	offset_y = 10;
	ij.x = -1;
	while (game()->input_data->map[++ij.x])
	{
		ij.y = -1;
		while (game()->input_data->map[++ij.y])
			draw_worldmap_tile(ij, size, offset_x, offset_y, id);
	}
}

void	hud_toogle_worldmap(bool change_state, int id)
{
	static bool	worldmap = false;

	if (change_state)
		worldmap = !worldmap;
	if (!worldmap)
	{
		if (player(id)->worldmap)
		{
			mlx_delete_image(player(id)->mlx, player(id)->worldmap);
			player(id)->worldmap = NULL;
		}
		return ;
	}
	player(id)->worldmap = mlx_new_image(player(id)->mlx, 1000, 1000);
	draw_worldmap(id);
	mlx_image_to_window(player(id)->mlx, player(id)->worldmap, 300, 300);
}
