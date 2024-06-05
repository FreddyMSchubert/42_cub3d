/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:47:07 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/05 18:52:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define RIGHT 0
#define DOWN 1

/*
	To remove unnecessary double walls and invisible walls, if a wall is placed
	somewhere there is already a wall (thus, the wall is not visible),
	no wall gets placed.
*/

// top edge, left edge, right edge, bottom edge
static void	add_wall(bool ***bool_map, t_input_data *in, t_scale pos,
								t_scale size)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y)
		return ;
	if (wall_needed(in->map, pos.x, pos.y - 1, size))
		bool_map[pos.y][pos.x][RIGHT] = !bool_map[pos.y][pos.x][RIGHT];
	if (wall_needed(in->map, pos.x - 1, pos.y, size))
		bool_map[pos.y][pos.x][DOWN] = !bool_map[pos.y][pos.x][DOWN];
	if (pos.x + 1 < size.x && wall_needed(in->map, pos.x + 1, pos.y, size))
		bool_map[pos.y][pos.x + 1][DOWN] = !bool_map[pos.y][pos.x + 1][DOWN];
	if (pos.y + 1 < size.y && wall_needed(in->map, pos.x, pos.y + 1, size))
		bool_map[pos.y + 1][pos.x][RIGHT] = !bool_map[pos.y + 1][pos.x][RIGHT];
}

/*
	By saving the data of where to place a wall into a boolean
	array, we can easily remove redundant walls.

	Because false is 0 and gc_malloc initializes the memory to 0,
	we don't need to set the values to false after allocation.
*/

static bool	***get_bool_array(t_input_data *in, t_scale size)
{
	bool	***bool_map;
	int		y;
	int		x;

	bool_map = gc_malloc(sizeof(bool **) * (size.y + 1));
	y = -1;
	while (++y < size.y)
	{
		bool_map[y] = gc_malloc(sizeof(bool *) * (size.x + 1));
		x = -1;
		while (++x < size.x)
			bool_map[y][x] = gc_malloc(sizeof(bool) * 2);
		bool_map[y][x] = NULL;
	}
	bool_map[y] = NULL;
	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
			if (*in->map[y][x] == WALL)
				add_wall(bool_map, in, (t_scale){x, y}, size);
	}
	return (bool_map);
}

static int	count_walls(bool ***walls, t_scale size)
{
	int	walls_count;
	int	y;
	int	x;

	walls_count = 0;
	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
		{
			if (walls[y][x] != NULL)
			{
				if (walls[y][x][RIGHT] == true)
					walls_count++;
				if (walls[y][x][DOWN] == true)
					walls_count++;
			}
		}
	}
	return (walls_count);
}

/*
	The return of this file is a list of wall side transforms,
	created from the boolean array.
*/

static t_transform	**create_walls_list(bool ***bool_list, t_scale size)
{
	t_transform	**walls;
	int			walls_count;
	int			y;
	int			x;

	walls_count = count_walls(bool_list, size);
	walls = gc_malloc(sizeof(t_transform *) * (walls_count + 1));
	walls[walls_count] = NULL;
	y = -1;
	walls_count = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
		{
			if (bool_list[y][x] != NULL)
			{
				if (bool_list[y][x][RIGHT] == true)
					walls[++walls_count] = create_transform(x, y, 1, 0);
				if (bool_list[y][x][DOWN] == true)
					walls[++walls_count] = create_transform(x, y, 0, 1);
			}
		}
	}
	return (walls);
}

void	convert_walls(void)
{
	t_scale			size;
	bool			***bool_map;
	t_input_data	*in;

	in = game()->input_data;
	size = get_map_size(in->map);
	bool_map = get_bool_array(in, size);
	in->walls = create_walls_list(bool_map, size);
}
