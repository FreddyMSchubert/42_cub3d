/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:49:10 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/06 09:50:22 by fschuber         ###   ########.fr       */
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
				printf("%s%c%s", ANSI_BACKGROUND_BLACK, mode[0], ANSI_RESET);
			else if (current_spot == FLOOR)
				printf("%s%c%s", ANSI_BACKGROUND_GREEN, mode[1], ANSI_RESET);
			else if (current_spot == WALL)
				printf("%s%c%s", ANSI_BACKGROUND_RED, mode[2], ANSI_RESET);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	print_walls(void)
{
	t_input_data	*in;
	int				i;

	in = game()->input_data;
	i = -1;
	while (in && in->walls && in->walls[++i] != NULL)
	{
		printf("{'x': %f, 'y':%f, 'dx': %f, 'dy': %f},\n",
			in->walls[i]->pos.x,
			in->walls[i]->pos.y,
			in->walls[i]->rot.x,
			in->walls[i]->rot.y);
	}
}
