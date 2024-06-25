/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:54:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/25 11:40:10 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define INVALID -1

int	flood_fill(t_input_data *data, bool **visited, \
				t_scale pos, t_scale map_size)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= map_size.x || \
		pos.y >= map_size.y || *(data->map[pos.y][pos.x]) == VOID)
		return (INVALID);
	if (visited[pos.y][pos.x] == true)
		return (0);
	visited[pos.y][pos.x] = true;
	if (*(data->map[pos.y][pos.x]) == FLOOR)
	{
		if (flood_fill(data, visited, (t_scale){pos.x + 1, pos.y}, \
												map_size) == INVALID)
			return (INVALID);
		if (flood_fill(data, visited, (t_scale){pos.x - 1, pos.y}, \
												map_size) == INVALID)
			return (INVALID);
		if (flood_fill(data, visited, (t_scale){pos.x, pos.y + 1}, \
												map_size) == INVALID)
			return (INVALID);
		if (flood_fill(data, visited, (t_scale){pos.x, pos.y - 1}, \
												map_size) == INVALID)
			return (INVALID);
	}
	return (0);
}

void	clear_unused_spaces(t_tile_type ***map, \
						bool **visited, t_scale map_size)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map_size.y)
	{
		x = -1;
		while (++x < map_size.x)
			if (visited[y][x] == false)
				*map[y][x] = VOID;
	}
}

void	validate(void)
{
	t_input_data	*data;
	int				y;
	t_scale			map_size;
	bool			**visited;

	data = game()->input_data;
	map_size.x = 0;
	map_size.y = 0;
	while (data->map[map_size.y] != NULL)
		map_size.y++;
	while (data->map[0][map_size.x] != NULL)
		map_size.x++;
	visited = gc_malloc(map_size.y * sizeof(bool *));
	y = -1;
	while (++y < map_size.y)
		visited[y] = gc_malloc(map_size.x * sizeof(bool));
	if (flood_fill(data, visited, (t_scale){player()->spawn_transform.pos.x, \
						player()->spawn_transform.pos.y}, map_size) == INVALID)
		cub_exit("Invalid map - Player can reach edge or void.", -1);
	clear_unused_spaces(data->map, visited, map_size);
}
