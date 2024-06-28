/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_drawer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:19:53 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/28 11:03:19 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	get_tex_color_at(mlx_texture_t *tex, int x, int y);

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
			if ((color & 0xFF) > 0)
				mlx_put_pixel(game()->game_scene, x, y, color);
		}
	}
}