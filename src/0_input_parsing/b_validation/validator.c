/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:54:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/22 11:32:30 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	check_wall_valid(t_input_data data, int x, int y)
{
	if (!data.map || x == 0 || y == 0 || !data.map[y] || !data.map[y][x])
		return (false);
	if (!data.map[y + 1])
		return (false);
	if (!data.map[y - 1])
		return (false);
	if (!data.map[y][x + 1])
		return (false);
	if (!data.map[y][x - 1])
		return (false);
	if (data.map[y + 1][x] == VOID)
		return (false);
	if (data.map[y - 1][x] == VOID)
		return (false);
	if (data.map[y][x + 1] == VOID)
		return (false);
	if (data.map[y][x - 1] == VOID)
		return (false);
	return (true);
}

void	validate(t_input_data data)
{
	int	x;
	int	y;

	y = -1;
	while (data.map[++y])
	{
		x = -1;
		while (data.map[y][++x])
		{
			if (data.map[y][x] == FLOOR)
			{
				if (!check_wall_valid(data, x, y))
				{
					logger('e', "Invalid map.");
					gc_exit_error();
				}
			}
		}
	}
}
