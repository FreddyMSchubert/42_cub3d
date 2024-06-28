/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:46:53 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 19:29:26 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	get_shuffled_directions(int dx[], int dy[])
{
	int	i;
	int	r;
	int	temp_dx;
	int	temp_dy;

	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 2;
	dx[3] = -2;
	dy[0] = 2;
	dy[1] = -2;
	dy[2] = 0;
	dy[3] = 0;
	i = 0;
	while (i < 4)
	{
		r = random_int(0, 3);
		temp_dx = dx[i];
		temp_dy = dy[i];
		dx[i] = dx[r];
		dy[i] = dy[r];
		dx[r] = temp_dx;
		dy[r] = temp_dy;
		i++;
	}
}

static void	generate_maze(char **maze, bool **visited, t_scale pos, t_scale size)
{
	int		dx[4];
	int		dy[4];
	int		i;
	t_scale	new_pos;
	t_scale	mid_pos;

	get_shuffled_directions(dx, dy);
	visited[pos.y][pos.x] = true;
	maze[pos.y][pos.x] = '0';
	i = -1;
	while (++i < 4)
	{
		new_pos.x = pos.x + dx[i];
		new_pos.y = pos.y + dy[i];
		mid_pos.x = (pos.x + new_pos.x) / 2;
		mid_pos.y = (pos.y + new_pos.y) / 2;
		if (new_pos.x > 0 && new_pos.x < size.x - 1 && new_pos.y > 0 && \
					new_pos.y < size.y - 1 && !visited[new_pos.y][new_pos.x] && \
					mid_pos.x > 0 && mid_pos.x < size.x - 1 && mid_pos.y > 0 && mid_pos.y < size.y - 1)
		{
			maze[mid_pos.y][mid_pos.x] = '0';
			generate_maze(maze, visited, new_pos, size);
		}
	}
}

static inline void	setup_maze(char ***maze, bool ***visited, t_scale map_scale)
{
	int	x;
	int	y;

	*maze = gc_malloc(map_scale.y * sizeof(char *));
	*visited = gc_malloc(map_scale.y * sizeof(bool *));
	y = -1;
	while (++y < map_scale.y)
	{
		(*maze)[y] = gc_malloc(map_scale.x * sizeof(char));
		(*visited)[y] = gc_malloc(map_scale.x * sizeof(bool));
		x = -1;
		while (++x < map_scale.x)
		{
			(*maze)[y][x] = '1';
			(*visited)[y][x] = false;
		}
	}
}

void	generate_map(void)
{
	t_scale	map_scale;
	char	**maze;
	bool	**visited;

	map_scale = (t_scale){random_int(MIN_MAP_SIZE, MAX_MAP_SIZE), random_int(MIN_MAP_SIZE, MAX_MAP_SIZE)};
	setup_maze(&maze, &visited, map_scale);
	generate_maze(maze, visited, (t_scale){random_int(1, map_scale.y - 2), random_int(1, map_scale.x - 2)}, map_scale);
	place_player_spawn(maze, map_scale);
	logger(LOGGER_STEP, "Player spawn placed");
	remove_walls(maze, map_scale.y, map_scale.x);
	logger(LOGGER_STEP, "Walls removed");
	add_rooms(maze, map_scale, random_int(MIN_ROOMS_AMOUNT, MAX_ROOMS_AMOUNT));
	logger(LOGGER_STEP, "Rooms added");
	write_cub_file(maze, map_scale.y, map_scale.x, "generated_map.cub");
	logger(LOGGER_INFO, "Map saved to generated_map.cub");
	gc_cleanup_and_reinit();
}