/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/24 14:21:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	draw_square(int x, int y, int size, int color)
{
	int			i;
	int			j;
	mlx_image_t	*image;

	image = game()->game_scene;
	if (!image)
		return ;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (x >= 0 && x < (int)(image->width)
				&& y >= 0 && y < (int)(image->height))
			{
				mlx_put_pixel(image, x + i, y + j, color);
			}
		}
	}
}
