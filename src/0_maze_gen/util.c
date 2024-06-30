/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:22:43 by freddy            #+#    #+#             */
/*   Updated: 2024/06/30 10:24:56 by freddy           ###   ########.fr       */
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

void	print_mapmaker_map(char **maze, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			write(STDOUT_FILENO, &maze[i][j], 1);
			j++;
		}
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
