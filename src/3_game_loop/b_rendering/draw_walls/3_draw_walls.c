/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/13 09:25:26 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static bool	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
	{
		mlx_put_pixel(img, x, y, col);
		return (true);
	}
	return (false);
}

static int	get_color(char walldir)
{
	if (walldir == 'N')
		return (t_color_to_int((t_color){255, 0, 0, 255}));
	if (walldir == 'E')
		return (t_color_to_int((t_color){0, 0, 255, 255}));
	if (walldir == 'S')
		return (t_color_to_int((t_color){0, 255, 0, 255}));
	if (walldir == 'W')
		return (t_color_to_int((t_color){255, 255, 0, 255}));
	return (t_color_to_int((t_color){255, 255, 255, 255}));
}

void	draw_wall(int x_pixel, int height, char d)
{
	int		color;
	int		start_y;
	int		end_y;
	int		y;

	color = get_color(d);
	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = (int)(game()->mlx->height / 2) + height / 2;
	y = start_y;
	while (y < end_y)
	{
		set_pixel_color(game()->game_scene, x_pixel, y, color);
		y++;
	}
}
