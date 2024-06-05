/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:50:16 by freddy            #+#    #+#             */
/*   Updated: 2024/05/29 08:53:18 by freddy           ###   ########.fr       */
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
			if (maze[i][j] == '1' && random_int(1, 100) < WALL_REMOVAL_CHANCE_PERCENT)
				maze[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	place_player_spawn(char **maze, t_scale	map_scale)
{
    int found_pos;
    int x;
    int y;

    found_pos = false;
    while (found_pos == false)
    {
        x = random_int(1, map_scale.x - 2);
        y = random_int(1, map_scale.y - 2);
        if (x <= 0 || y <= 0)
            continue ;
        if (x >= map_scale.x - 1 || y >= map_scale.y - 1)
            continue ;
        found_pos = true;
        maze[y][x] = "NSWE"[random_int(0, 3)];
    }
}

static void	add_room(char **maze, t_scale start_pos, t_scale room_scale, t_scale maze_size)
{
	int	x;
	int	y;

	x = start_pos.x - 1;
	while (++x < start_pos.x + room_scale.y)
	{
		y = start_pos.y - 1;
		while (++y < start_pos.y + room_scale.x)
        {
            if (x > 0 && y > 0 && x < maze_size.y - 1 && y < maze_size.x - 1)
            maze[x][y] = '0';
        }
	}
}

void	add_rooms(char **maze, t_scale scale, int room_count)
{
	int		smaller;
	t_scale	room_scale;
    t_scale start_pos;
	int		i;

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
        start_pos.x = random_int(1, scale.x - room_scale.y - 2);
        start_pos.y = random_int(1, scale.y - room_scale.x - 2);
		add_room(maze, start_pos, room_scale, scale);
	}
}
