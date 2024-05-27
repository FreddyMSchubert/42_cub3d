/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:13:03 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/24 13:40:00 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

t_scale	get_map_size(t_tile_type ***map)
{
	t_scale			size;
	int				i;
	int				j;

	size.x = 0;
	size.y = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j > size.x)
			size.x = j;
		i++;
	}
	size.y = i;
	return (size);
}

t_transform	*create_transform(int x, int y, int rotx, int roty)
{
	t_transform	*directions;

	directions = gc_malloc(sizeof(t_transform));
	directions->pos.x = x;
	directions->pos.y = y;
	directions->rot.x = rotx;
	directions->rot.y = roty;
	return (directions);
}

/*
	Returns if a given space is empty, e.g. voids or out of bounds.
*/
bool	wall_needed(t_tile_type ***map, int x, int y, t_scale size)
{
	if (x < 0 || y < 0 || x >= size.x || y >= size.y)
		return (false);
	if (map[y] && map[y][x] && *map[y][x] == VOID)
		return (false);
	return (true);
}
