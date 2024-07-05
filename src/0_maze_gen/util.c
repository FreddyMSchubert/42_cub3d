/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 20:22:43 by freddy            #+#    #+#             */
/*   Updated: 2024/07/05 13:12:40 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_adjacent_walls(char **maze, t_scale pos, t_scale scale)
{
	int	wall_count;

	wall_count = 0;
	if (pos.x == 0 || pos.y == 0 || \
		pos.x == scale.x - 1 || pos.y == scale.y - 1)
		return (4);
	wall_count += maze[pos.y - 1][pos.x] == '1';
	wall_count += maze[pos.y + 1][pos.x] == '1';
	wall_count += maze[pos.y][pos.x - 1] == '1';
	wall_count += maze[pos.y][pos.x + 1] == '1';
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
