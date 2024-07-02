/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   features_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:30:39 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/02 11:41:25 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	place_health_drops(char **maze, t_scale scale)
{
	int	x;
	int	y;

	y = 1;
	while (y < scale.y - 2)
	{
		x = 1;
		while (x < scale.x - 2)
		{
			if (maze[y][x] == '0' && \
					random_int(1, 100) < HEALTH_DROP_CHANCE_PERCENT)
				maze[y][x] = 'h';
			x++;
		}
		y++;
	}
}
