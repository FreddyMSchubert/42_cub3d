/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:50:32 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/07 15:08:07 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

#define MAX_DISPLAYED_HEARTS 40

void	draw_healthbar(int size, int start_x, int start_y)
{
	int	i;
	int	step;
	int	max_hearts_in_bar;

	i = -1;
	step = -1;
	max_hearts_in_bar = 10;
	while (++i < player()->health && i < MAX_DISPLAYED_HEARTS)
	{
		if (++step >= max_hearts_in_bar)
		{
			start_y -= size + 5;
			step = 0;
		}
		texture_draw(game()->textures.health,
			(t_scale){start_x + size * step, start_y - size - 5}, \
							(t_scale){size, size});
	}
}

void	draw_boss_healthbar(int size)
{
	int	i;
	int	start_x;
	int	start_y;
	int	hearts;

	hearts = game()->boss->health;
	start_x = (game()->mlx->width - (hearts * size)) / 2;
	start_y = 5;
	i = -1;
	while (++i < hearts)
		texture_draw(game()->textures.health_boss,
			(t_scale){start_x + i * size, start_y},
			(t_scale){size, size});
}
