/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   healthbar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:50:32 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/01 15:38:37 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	draw_healthbar(int size, int start_x, int start_y)
{
	int	i;
	int	step;
	int	max_hearts_in_bar;

	i = -1;
	step = -1;
	max_hearts_in_bar = 10;
	while (++i < player()->health)
	{
		if (++step >= max_hearts_in_bar)
		{
			start_y -= size + 5;
			step = 0;
		}
		texture_draw(game()->textures.health,
			(t_scale){start_x + size * step, start_y - size - 5}, (t_scale){size, size});
	}
}