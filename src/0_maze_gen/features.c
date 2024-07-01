/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:50:16 by freddy            #+#    #+#             */
/*   Updated: 2024/06/30 12:05:11 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	remove_walls(char **maze, int height, int width)
{
	int	y;
	int	x;

	y = 1;
	while (y < height - 2)
	{
		x = 1;
		while (x < width - 2)
		{
			if (maze[y][x] == '1' && random_int(1, 100) < \
								WALL_REMOVAL_CHANCE_PERCENT)
				maze[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	place_player_spawn(char **maze, t_scale	map_scale)
{
	int	found_pos;
	int	x;
	int	y;

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

	y = start_pos.y - 1;
	while (++y < start_pos.y + room_scale.y)
	{
		x = start_pos.x - 1;
		while (++x < start_pos.x + room_scale.x)
		{
			if (x > 0 && y > 0 && x < maze_size.x - 1 && \
					y < maze_size.y - 1 && maze[y][x] == '1')
				maze[y][x] = '0';
		}
	}
}

void	add_rooms(char **maze, t_scale scale, int room_count)
{
	t_scale	room_scale;
	t_scale	start_pos;
	int		i;
	t_scale	max_room_size;
	t_scale	min_room_size;

	i = -1;
	min_room_size.x = min(MIN_ROOM_SIZE, scale.x / MAX_ROOM_SIZE_REL_TO_MAP_SIZE);
	min_room_size.y = min(MIN_ROOM_SIZE, scale.y / MAX_ROOM_SIZE_REL_TO_MAP_SIZE);
	max_room_size.x = min(MAX_ROOM_SIZE, scale.x / MAX_ROOM_SIZE_REL_TO_MAP_SIZE);
	max_room_size.y = min(MAX_ROOM_SIZE, scale.y / MAX_ROOM_SIZE_REL_TO_MAP_SIZE);
	while (++i < room_count)
	{
		room_scale.x = random_int(min_room_size.x, max_room_size.x);
		room_scale.y = random_int(min_room_size.y, max_room_size.y);
		start_pos.x = random_int(1, scale.x - room_scale.y - 2);
		start_pos.y = random_int(1, scale.y - room_scale.x - 2);
		if (room_scale.x <= 0 || room_scale.y <= 0)
			continue ;
		if (start_pos.x <= 0 || start_pos.y <= 0)
			continue ;
		add_room(maze, start_pos, room_scale, scale);
	}
}

void	place_key(char **maze, t_scale scale)
{
	int	required_walls;

	required_walls = 3;
	while (required_walls >= 0)
	{
		for (int i = 0; i < scale.x * scale.y; i++)
		{
			int x = random_int(1, scale.x - 2);
			int y = random_int(1, scale.y - 2);
			if (maze[y][x] == '0' && count_adjacent_walls(maze, x, y, scale.y, scale.x) == required_walls)
			{
				maze[y][x] = 'K';
				return ;
			}
		}
	}
	logger(LOGGER_WARNING, "Could not place key in maze. I guess you're stuck here forever.");
}
