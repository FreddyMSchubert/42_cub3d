/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:19:53 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/03 10:15:51 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	texture_draw(mlx_texture_t *texture, t_scale pos, t_scale size)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	x = pos.x - 1;
	while (++x < pos.x + size.x)
	{
		y = pos.y - 1;
		while (++y < pos.y + size.y)
		{
			tex_x = (int)((x - pos.x) * texture->width / size.x);
			tex_y = (int)((y - pos.y) * texture->height / size.y);
			color = get_tex_color_at(texture, tex_x, tex_y);
			if ((color & 0xFF) > 0 && x >= 0
				&& (int32_t)x < game()->mlx->width
				&& y >= 0 && (int32_t)y < game()->mlx->height)
				mlx_put_pixel(game()->game_scene, x, y, color);
		}
	}
}
