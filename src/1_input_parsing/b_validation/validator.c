/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:54:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/28 23:06:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define INVALID -1

void flood_fill(t_input_data *data, bool **visited, int x, int y, int *invalid_flag, t_scale map_size)
{
	if (*invalid_flag == INVALID)
		return;
	if (x < 0 || y < 0 || x >= map_size.x || y >= map_size.y || *(data->map[y][x]) == VOID)
	{
		*invalid_flag = INVALID;
		return;
	}
	if (visited[y][x] == true)
		return ;
	visited[y][x] = true;
	if (*(data->map[y][x]) == FLOOR)
	{
		flood_fill(data, visited, x + 1, y, invalid_flag, map_size);
		flood_fill(data, visited, x - 1, y, invalid_flag, map_size);
		flood_fill(data, visited, x, y + 1, invalid_flag, map_size);
		flood_fill(data, visited, x, y - 1, invalid_flag, map_size);
	}
}

void	validate(void)
{
	t_input_data	*data;
	int				invalid;
	int				x;
	int				y;
	t_scale			map_size;
	bool			**visited;

	data = get_persistent_data()->input_data;
	invalid = 0;
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
	printf("y: %f, x: %f\n", get_player()->spawn_point.y, get_player()->spawn_point.x);
	flood_fill(data, visited, get_player()->spawn_point.x, get_player()->spawn_point.y, &invalid, map_size);
	if (invalid == INVALID)
		cub_exit_error("Invalid map. Player can reach edge or void. [Validator]");
	y = -1;
	while (++y < map_size.y)
	{
		x = -1;
		while (++x < map_size.x)
			if (visited[y][x] == false)
				*data->map[y][x] = VOID;
	}
}
