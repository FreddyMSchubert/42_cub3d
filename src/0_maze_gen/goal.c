/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:25:23 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 20:58:36 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline bool	place_door_and_goal(char **maze, int height, int width)
{
	bool	vertical;
	t_scale	door1;
	t_scale	door2;
	char	door_dir;

	for (int y = 1; y < height - 1; y++)
	{
		for (int x = 1; x < width - 1; x++)
		{
			// Check for an initial corridor entry condition
			if (maze[y][x] == '0' && count_adjacent_walls(maze, x, y, height, width) == 2)
			{
				if (maze[y][x - 1] == '0' && maze[y][x + 1] == '0')
					vertical = false;
				else if (maze[y - 1][x] == '0' && maze[y + 1][x] == '0')
					vertical = true;
				else
					continue ;

				printf("Selected pos is vertical: %d\n", vertical);

				door1.x = x;
				door1.y = y;
				door2.x = x;
				door2.y = y;
				if (vertical)
				{
					door1.y = y - 1;
					door2.y = y + 1;
				}
				else
				{
					door1.x = x - 1;
					door2.x = x + 1;
				}

				// make sure we have a hallway
				if (!(count_adjacent_walls(maze, door1.x, door1.y, height, width) >= 2) || !(count_adjacent_walls(maze, door2.x, door2.y, height, width) >= 2))
					continue ;
				if (vertical)
				{
					if (maze[door1.y][door1.x - 1] != '1' || maze[door1.y][door1.x + 1] != '1')
						continue ;
				}
				else
				{
					if (maze[door1.y - 1][door1.x] != '1' || maze[door1.y + 1][door1.x] != '1')
						continue ;
				}
				printf("alright we have proper 2 walls next to each segment!\n");

				door_dir = (vertical) ? 'H' : 'V';

				maze[door1.y][door1.x] = door_dir;
				maze[door2.y][door2.x] = door_dir;
				maze[y][x] = 'G';
				return (true);
			}
		}
	}
	return (false); // Return false if no suitable corridor was found
}

static inline void	place_goal_randomly(char **maze, t_scale map_scale)
{
	t_scale	pos;
	bool	placed;

	placed = false;
	while (!placed)
	{
		pos.x = random_int(1, map_scale.x - 1);
		pos.y = random_int(1, map_scale.y - 1);
		if (maze[pos.y][pos.x] == '0')
		{
			maze[pos.y][pos.x] = 'G';
			placed = true;
		}
	}
}

void	place_locked_goal(char **maze, t_scale	map_scale)
{
	if (!place_door_and_goal(maze, map_scale.y, map_scale.x))
	{
		logger(LOGGER_WARNING, "No suitable spot found for locked goal placement, placing goal randomly");
		place_goal_randomly(maze, map_scale);
	}
}
