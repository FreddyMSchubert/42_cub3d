/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:47:07 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 14:06:46 by fschuber         ###   ########.fr       */
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
static void	add_wall(bool ***bool_map, t_input_data *in, t_vec2 pos,
								t_size size)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= size.width || pos.y >= size.height)
		return ;
	if (wall_needed(in->map, pos.x, pos.y - 1, size))
		bool_map[pos.y][pos.x][RIGHT] = !bool_map[pos.y][pos.x][RIGHT];
	if (wall_needed(in->map, pos.x - 1, pos.y, size))
		bool_map[pos.y][pos.x][DOWN] = !bool_map[pos.y][pos.x][DOWN];
	if (pos.x + 1 < size.width && wall_needed(in->map, pos.x + 1, pos.y, size))
		bool_map[pos.y][pos.x + 1][DOWN] = !bool_map[pos.y][pos.x + 1][DOWN];
	if (pos.y + 1 < size.height && wall_needed(in->map, pos.x, pos.y + 1, size))
		bool_map[pos.y + 1][pos.x][RIGHT] = !bool_map[pos.y + 1][pos.x][RIGHT];
}

/*
	By saving the data of where to place a wall into a boolean
	array, we can easily remove redundant walls.

	Because false is 0 and gc_malloc initializes the memory to 0,
	we don't need to set the values to false after allocation.
*/

static bool	***get_bool_array(t_input_data *in, t_size size)
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
			bool_map[y][x] = gc_malloc(sizeof(bool) * 2);
		bool_map[y][x] = NULL;
	}
	bool_map[y] = NULL;
	y = -1;
	while (++y < size.height)
	{
		x = -1;
		while (++x < size.width)
			if (*in->map[y][x] == WALL)
				add_wall(bool_map, in, (t_vec2){x, y}, size);
	}
	return (bool_map);
}

static int	count_walls(bool ***walls, t_size size)
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

static t_transform	**create_walls_list(bool ***bool_list, t_size size)
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

void	convert_walls(void)
{
	t_size			size;
	bool			***bool_map;
	t_input_data	*in;

	in = get_persistent_data()->input_data;
	size = get_map_size(in->map);
	bool_map = get_bool_array(in, size);
	in->walls = create_walls_list(bool_map, size);
}

/*
t_tile_type ***create_map() {
    t_tile_type*** map = malloc(6 * sizeof(t_tile_type**));
    if (map == NULL) {
        perror("Failed to allocate map");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        map[i] = malloc(6 * sizeof(t_tile_type*));
        if (map[i] == NULL) {
            perror("Failed to allocate row");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 5; j++) {
            map[i][j] = malloc(sizeof(t_tile_type));
            if (map[i][j] == NULL) {
                perror("Failed to allocate cell");
                exit(EXIT_FAILURE);
            }
            *map[i][j] = WALL;
        }
        map[i][5] = NULL;
    }
    map[5] = NULL;

    *map[1][1] = FLOOR; *map[1][2] = FLOOR; *map[1][3] = FLOOR;
    *map[2][1] = FLOOR; *map[2][3] = FLOOR;
    *map[3][1] = FLOOR; *map[3][2] = FLOOR; *map[3][3] = FLOOR;

    return map;
}

int main() {
	// Create a test map
	t_tile_type ***map = create_map();

	// Set up input data
	t_input_data in;
	in.map = map;

	// Convert walls using provided map data
	convert_walls(&in);

	// Print the wall transformations
	print_walls();

	// Assuming there is proper cleanup code for gc_malloc allocations
	// Cleanup code here...

	return 0;
}
*/