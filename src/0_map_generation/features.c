/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:50:16 by freddy            #+#    #+#             */
/*   Updated: 2024/05/28 23:35:50 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	remove_walls(char **maze, int height, int width)
{
	int	i;
	int	j;

	i = 2;
	while (i < height - 4)
	{
		j = 2;
		while (j < width - 4)
		{
			if (maze[i][j] == '1' && random_int(1, 100) < 10)
				maze[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	place_player_spawn(char **maze, t_scale map_scale, \
								t_scale starting_pos)
{
	maze[starting_pos.y][starting_pos.x] = \
						"NSWE"[random_int(0, 3)];
}

static void	add_room(char **maze, int start_x, int start_y, t_scale room_scale)
{
	int	x;
	int	y;

	x = start_x - 1;
	while (++x < start_x + room_scale.y)
	{
		y = start_y - 1;
		while (++y < start_y + room_scale.x)
			maze[x][y] = '0';
	}
}

void	add_rooms(char **maze, t_scale scale, int room_count)
{
	int		smaller;
	t_scale	room_scale;
	int		i;
	int		start_x;
	int		start_y;

	smaller = scale.x;
	if (scale.y < scale.x)
		smaller = scale.y;
	i = -1;
	while (++i < room_count)
	{
		room_scale.x = random_int(1, smaller / 2);
		room_scale.y = random_int(1, smaller / 2);
		room_scale.x %= 15;
		room_scale.y %= 15;
		start_x = random_int(1, scale.x - room_scale.y - 1);
		start_y = random_int(1, scale.y - room_scale.x - 1);
		add_room(maze, start_x, start_y, room_scale);
	}
}
