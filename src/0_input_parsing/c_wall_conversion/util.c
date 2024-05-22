/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:13:03 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/22 08:03:58 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

struct s_size	get_map_size(t_tile_type **map)
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
