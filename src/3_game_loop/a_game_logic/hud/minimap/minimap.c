/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker            #+#    #+#            */
/*   Updated: 2024/06/24 10:13:05 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../../include/cub3d.h"

static inline bool	is_visible(int x, int y)
{
	float player_x = player()->transform.pos.x;
	float player_y = player()->transform.pos.y;
	float player_rot_x = player()->transform.rot.x;
	float player_rot_y = player()->transform.rot.y;
	float dir_x = x - player_x;
	float dir_y = y - player_y;
	float dir_magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);
	dir_x /= dir_magnitude;
	dir_y /= dir_magnitude;
	float player_rot_magnitude = sqrt(player_rot_x * player_rot_x + player_rot_y * player_rot_y);
	player_rot_x /= player_rot_magnitude;
	player_rot_y /= player_rot_magnitude;
	float dot_product = dir_x * player_rot_x + dir_y * player_rot_y;
	float angle = acos(dot_product);
	const float MAX_VIEW_ANGLE = M_PI / 4; // 90 degrees in radians
	const float MAX_DISTANCE = VIEW_DIST * 2; // Example visibility distance
	if (angle <= MAX_VIEW_ANGLE && dir_magnitude <= MAX_DISTANCE)
		return (true);
	return (false);
}

static int	get_opacity(int x, int y)
{
	double	distance;
	int		min_opacity;
	int		max_opacity;

	min_opacity = 75;
	max_opacity = 255;
	distance = sqrt(pow(player()->transform.pos.x - x, 2)
			+ pow(player()->transform.pos.y - y, 2));
	if (!is_visible(x, y) || distance >= 100)
		return (min_opacity);
	if (distance < 10)
		return (255);
	else if (distance < 25)
		return (200);
	return (150);
}

static inline void	draw_walls(void)
{
	int			i;
	int			j;
	int			wall_size;
	t_tile_type	***walls;

	i = -1;
	walls = game()->input_data->map;
	wall_size = 5;
	while (walls[++i])
	{
		j = -1;
		while (walls[i][++j])
		{
			if (*(walls[i][j]) == VOID)
				draw_square(j * wall_size + MINIMAP_LEFT_OFFSET,
					i * wall_size + MINIMAP_TOP_OFFSET, wall_size,
					rgba_to_int(50, 50, 50, get_opacity(i, j)));
			else if (*(walls[i][j]) == WALL)
				draw_square(j * wall_size + MINIMAP_LEFT_OFFSET,
					i * wall_size + MINIMAP_TOP_OFFSET, wall_size,
					rgba_to_int(255, 255, 255, get_opacity(i, j)));
			else if (*(walls[i][j]) == FLOOR)
				draw_square(j * wall_size + MINIMAP_LEFT_OFFSET,
					i * wall_size + MINIMAP_TOP_OFFSET, wall_size,
					rgba_to_int(0, 0, 0, get_opacity(j, i)));
		}
	}
}

// static inline void	draw_player(void)
// {
// 	draw_square(player()->transform.pos.y + MINIMAP_LEFT_OFFSET + 4,
	// player()->transform.pos.x + MINIMAP_TOP_OFFSET + 4, 3,
	// rgba_to_int(255, 0, 0, 255));
// }

void	hud_draw_minimap(void)
{
	// draw_square(MINIMAP_LEFT_OFFSET, MINIMAP_TOP_OFFSET, MINIMAP_WIDTH,
	// 	rgba_to_int(50, 50, 50, 255));
	draw_walls();
	// draw_player();
}
