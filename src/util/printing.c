/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 08:35:32 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 08:42:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Mode determines what to print for each tile type,
// [0] for VOID, [1] for FLOOR, [2] for WALL
// Pass NULL for default
void	print_map(t_tile_type ***map, char *mode)
{
	int	x;
	int	y;
	int	current_spot;

	if (!mode)
		mode = " .#";
	y = 0;
	while (map && map[y] != NULL && ft_strlen(mode) == 3)
	{
		x = 0;
		while (map[y][x] != NULL)
		{
			current_spot = *map[y][x];
			if (current_spot == VOID)
				printf("%c", mode[0]);
			else if (current_spot == FLOOR)
				printf("%c", mode[1]);
			else if (current_spot == WALL)
				printf("%c", mode[2]);
			x++;
		}
		printf("\n");
		y++;
	}
}
