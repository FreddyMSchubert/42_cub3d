/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:47:07 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 15:11:16 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define RIGHT 0
#define DOWN 1

struct s_size
{
	int	width;
	int	height;
};

struct s_size	get_size(char **map)
{
	struct s_size	size;
	int				i;
	int				j;

	size.width = 0;
	size.height = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > size.width)
			size.width = j;
		i++;
	}
	size.height = i;
	return (size);
}

static t_transform	set_wall_values(int x, int y, int rotx, int roty)
{
	t_transform	directions;

	directions.pos.x = x;
	directions.pos.y = y;
	directions.rot.x = rotx;
	directions.rot.y = roty;
	return (directions);
}

void	add_wall(bool ***walls, int x, int y, struct s_size size)
{
	walls[y][x][RIGHT] = walls[y][x][RIGHT] && false;
	walls[y][x][DOWN] = walls[y][x][DOWN] && false;

	if (x + 1 < size.width)
		walls[y][x + 1][RIGHT] = walls[y][x + 1][RIGHT] && false;

	if (y + 1 < size.height)
		walls[y + 1][x][DOWN] = walls[y + 1][x][DOWN] && false;
}

t_input_data	*convert_walls(t_input_data *in)
{
	struct s_size	size;
	bool			***walls;
	int				y;
	int				x;

	size = get_size(in->map);
	walls = gc_malloc(sizeof(bool **) * (size.height + 1));
	y = -1;
	while (++y < size.height)
	{
		walls[y] = gc_malloc(sizeof(bool *) * (size.width + 1));
		x = -1;
		while (++x < size.width)
			if (in->map[x][y] == WALL)
				in->map[x][y] = gc_malloc(sizeof(bool) * 2);
		walls[y][x] = NULL;
	}
	y = -1;
	while (++y < size.height)
	{
		x = -1;
		while (++x < size.width)
			if (in->map[x][y] == WALL)
				add_wall(walls, x, y, size);
	}
}
