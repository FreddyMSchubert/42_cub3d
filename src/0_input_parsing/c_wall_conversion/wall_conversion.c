/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:47:07 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/22 08:04:21 by fschuber         ###   ########.fr       */
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

static void	add_wall(bool ***bool_map, int x, int y, struct s_size size)
{
	bool_map[y][x][RIGHT] = !bool_map[y][x][RIGHT];
	bool_map[y][x][DOWN] = !bool_map[y][x][DOWN];
	if (x + 1 < size.width)
		bool_map[y][x + 1][RIGHT] = !bool_map[y][x + 1][RIGHT];
	if (y + 1 < size.height)
		bool_map[y + 1][x][DOWN] = !bool_map[y + 1][x][DOWN];
}

/*
	By saving the data of where to place a wall into a boolean
	array, we can easily remove redundant walls.

	Because false is 0 and gc_malloc initializes the memory to 0,
	we don't need to set the values to false after allocation.
*/

static bool	***get_bool_array(t_input_data *in, struct s_size size)
{
	bool	***bool_map;
	int		y;
	int		x;

	bool_map = gc_malloc(sizeof(bool **) * (size.height + 1));
	y = -1;
	while (++y < size.height)
	{
		bool_map[y] = gc_malloc(sizeof(bool *) * (size.width + 1));
		x = -1;
		while (++x < size.width)
			if (in->map[y][x] == WALL)
				bool_map[y][x] = gc_malloc(sizeof(bool) * 2);
		bool_map[y][x] = NULL;
	}
	bool_map[y] = NULL;
	y = -1;
	while (++y < size.height)
	{
		x = -1;
		while (++x < size.width)
			if (in->map[y][x] == WALL)
				add_wall(bool_map, x, y, size);
	}
	return (bool_map);
}

static int	count_walls(bool ***walls, struct s_size size)
{
	int	walls_count;
	int	y;
	int	x;

	walls_count = 0;
	y = -1;
	while (++y < size.height)
	{
		x = -1;
		while (++x < size.width)
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

static t_transform	**create_walls_list(bool ***bool_list, struct s_size size)
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
	while (++y < size.height)
	{
		x = -1;
		while (++x < size.width)
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

void	convert_walls(t_input_data *in)
{
	struct s_size	size;
	bool			***bool_map;

	size = get_map_size(in->map);
	bool_map = get_bool_array(in, size);
	in->walls = create_walls_list(bool_map, size);
}
