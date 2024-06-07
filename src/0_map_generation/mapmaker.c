/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapmaker.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:46:53 by freddy            #+#    #+#             */
/*   Updated: 2024/06/07 09:58:23 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	get_shuffled_directions(int dx[], int dy[])
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

	get_shuffled_directions(dx, dy);
	visited[pos.x][pos.y] = true;
	maze[pos.x][pos.y] = '0';
	i = -1;
	while (++i < 4)
	{
		new_pos.x = pos.x + dx[i];
		new_pos.y = pos.y + dy[i];
		if (new_pos.x > 0 && new_pos.x < size.y - 1 && new_pos.y > 0 && \
					new_pos.y < size.x - 1 && !visited[new_pos.x][new_pos.y])
		{
			maze[(pos.x + new_pos.x) / 2][(pos.y + new_pos.y) / 2] = '0';
			generate_maze(maze, visited, new_pos, size);
		}
	}
}

static void	setup_maze(char ***maze, bool ***visited, t_scale map_scale)
{
	int	i;
	int	j;

	*maze = gc_malloc(map_scale.y * sizeof(char *));
	*visited = gc_malloc(map_scale.y * sizeof(bool *));
	i = -1;
	while (++i < map_scale.y)
	{
		j = -1;
		(*maze)[i] = gc_malloc(map_scale.x * sizeof(char));
		(*visited)[i] = gc_malloc(map_scale.x * sizeof(bool));
		while (++j < map_scale.x)
		{
			(*maze)[i][j] = '1';
			(*visited)[i][j] = false;
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
	write(STDOUT_FILENO, "Generating maze...\n", 19);
	generate_maze(maze, visited, (t_scale){random_int(1, map_scale.x - 2), random_int(1, map_scale.x - 2)}, map_scale);
	write(STDOUT_FILENO, "Maze generated\n", 15);
	place_player_spawn(maze, map_scale);
	write(STDOUT_FILENO, "Player spawn placed\n", 21);
	remove_walls(maze, map_scale.y, map_scale.x);
	write(STDOUT_FILENO, "Walls removed\n", 14);
	add_rooms(maze, map_scale, random_int(MIN_ROOMS_AMOUNT, MAX_ROOMS_AMOUNT));
	write(STDOUT_FILENO, "Rooms added\n", 12);
	write_cub_file(maze, map_scale.y, map_scale.x, "generated_maze.cub");
	write(STDOUT_FILENO, "Map saved to generated_maze.cub\n", 32);
}
