/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:25:23 by freddy            #+#    #+#             */
/*   Updated: 2024/07/07 18:13:47 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline t_scale	get_door_pos(char **maze, t_scale pos, t_scale scale)
{
	t_scale	door_pos;

	if (pos.y + 1 < scale.y && pos.y - 1 >= 0 && \
		pos.x + 1 < scale.x && pos.x - 1 >= 0)
	{
		if (maze[pos.y + 1][pos.x] == '0')
			door_pos = (t_scale){pos.x, pos.y + 1};
		else if (maze[pos.y - 1][pos.x] == '0')
			door_pos = (t_scale){pos.x, pos.y - 1};
		else if (maze[pos.y][pos.x + 1] == '0')
			door_pos = (t_scale){pos.x + 1, pos.y};
		else if (maze[pos.y][pos.x - 1] == '0')
			door_pos = (t_scale){pos.x - 1, pos.y};
		else
			return ((t_scale){-1, -1});
		if (count_adjacent_walls(maze, door_pos, scale) != 2)
			return ((t_scale){-1, -1});
		return (door_pos);
	}
	else
		return ((t_scale){-1, -1});
}

static inline bool	attempt_place_door_and_goal(char **maze, \
											t_scale pos, t_scale scale)
{
	t_scale	door_pos;
	bool	vertical;

	door_pos = get_door_pos(maze, pos, scale);
	if (door_pos.x == -1)
		return (false);
	if (door_pos.x == pos.x)
		vertical = true;
	else if (door_pos.y == pos.y)
		vertical = false;
	else
		return (false);
	if (vertical && (maze[door_pos.y][door_pos.x + 1] != '1' || \
		maze[door_pos.y][door_pos.x - 1] != '1'))
		return (false);
	if (!vertical && (maze[door_pos.y + 1][door_pos.x] != '1' || \
		maze[door_pos.y - 1][door_pos.x] != '1'))
		return (false);
	maze[pos.y][pos.x] = 'G';
	if (vertical)
		maze[door_pos.y][door_pos.x] = 'H';
	else
		maze[door_pos.y][door_pos.x] = 'V';
	return (true);
}

static inline bool	attempt_door_pos(char **maze, int height, int width)
{
	int		i;
	int		x;
	int		y;

	i = -1;
	while (++i < height * width)
	{
		x = random_int(1, width - 2);
		y = random_int(1, height - 2);
		if (maze[y][x] == '0' && count_adjacent_walls(maze, (t_scale){x, y}, \
					(t_scale){height, width}) == 3)
		{
			if (attempt_place_door_and_goal(maze, (t_scale){x, y}, \
											(t_scale){height, width}))
				return (true);
		}
	}
	return (false);
}

#define MAX_PLACE_ATTEMPTS 100

void	place_locked_goal(char **maze, t_scale map_scale)
{
	t_scale	pos;
	bool	placed;
	int		place_attempts;

	placed = false;
	if (!attempt_door_pos(maze, map_scale.y, map_scale.x))
	{
		logger(LOGGER_WARNING, "No perfect goal spot found, placing randomly.");
		place_attempts = 0;
		while (!placed)
		{
			place_attempts++;
			pos.x = random_int(1, map_scale.x - 2);
			pos.y = random_int(1, map_scale.y - 2);
			if (maze[pos.y][pos.x] == '0')
			{
				maze[pos.y][pos.x] = 'G';
				placed = true;
			}
		}
		if (place_attempts >= map_scale.x * map_scale.y)
			logger(LOGGER_WARNING, "Failed to place goal randomly. No goal!");
	}
}
