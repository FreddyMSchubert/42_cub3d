/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:50:32 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/02 10:40:53 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

#define MAX_DISPLAYED_HEARTS 30

void	draw_healthbar(int size, int start_x, int start_y)
{
	int	i;
	int	step;
	int	max_hearts_in_bar;

	i = -1;
	step = -1;
	max_hearts_in_bar = 10;
	while (++i < player()->health && i < 30)
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
