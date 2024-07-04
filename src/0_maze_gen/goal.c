/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:25:23 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 13:56:58 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	determine_door_pos(t_scale *door1, t_scale *door2, \
										bool v, t_scale goal)
{
	door1->x = goal.x;
	door1->y = goal.y;
	door2->x = goal.x;
	door2->y = goal.y;
	if (v)
	{
		door1->y = goal.y - 1;
		door2->y = goal.y + 1;
	}
	else
	{
		door1->x = goal.x - 1;
		door2->x = goal.x + 1;
	}
}

static inline void	place_door_and_goal(char **maze, t_scale door1, \
											t_scale door2, t_scale goal)
{
	char	door_dir;

	door_dir = 'V';
	if (door1.x == door2.x)
		door_dir = 'H';
	maze[door1.y][door1.x] = door_dir;
	maze[door2.y][door2.x] = door_dir;
	maze[goal.y][goal.x] = 'G';
}

static inline bool	attempt_place_door_and_goal(char **maze, t_scale s)
{
	bool	vertical;
	t_scale	door1;
	t_scale	door2;

	if (maze[s.y][s.x - 1] == '0' && maze[s.y][s.x + 1] == '0' && \
			maze[s.y - 1][s.x] == '1' && maze[s.y + 1][s.x] == '1')
		vertical = false;
	else if (maze[s.y - 1][s.x] == '0' && maze[s.y + 1][s.x] == '0' && \
			maze[s.y][s.x - 1] == '1' && maze[s.y][s.x + 1] == '1')
		vertical = true;
	else
		return (false);
	determine_door_pos(&door1, &door2, vertical, (t_scale){s.x, s.y});
	if (!(count_adjacent_walls(maze, door1, s) >= 2) || \
				!(count_adjacent_walls(maze, door2, s) >= 2))
		return (false);
	if (vertical && (maze[door1.y][door1.x - 1] != '1' || \
					maze[door1.y][door1.x + 1] != '1'))
		return (false);
	if (maze[door1.y - 1][door1.x] != '1' || maze[door1.y + 1][door1.x] != '1')
		return (false);
	place_door_and_goal(maze, door1, door2, s);
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
		if (maze[y][x] == '0')
		{
			if (attempt_place_door_and_goal(maze, (t_scale){x, y}))
				return (true);
		}
	}
	return (false);
}

#define MAX_PLACE_ATTEMPTS 100

void	place_locked_goal(char **maze, t_scale	map_scale)
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
		if (place_attempts >= MAX_PLACE_ATTEMPTS)
			logger(LOGGER_WARNING, "Failed to place goal randomly. No goal!");
	}
}
