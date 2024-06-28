/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:22:43 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 20:24:24 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int count_adjacent_walls(char **maze, int x, int y, int height, int width)
{
	int	wall_count;

	wall_count = 0;
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
		return (4);
	wall_count += (maze[y - 1][x] == '1') ? 1 : 0;
	wall_count += (maze[y + 1][x] == '1') ? 1 : 0;
	wall_count += (maze[y][x - 1] == '1') ? 1 : 0;
	wall_count += (maze[y][x + 1] == '1') ? 1 : 0;
	return (wall_count);
}
