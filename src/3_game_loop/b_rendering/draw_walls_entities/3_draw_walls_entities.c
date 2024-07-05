/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/07/05 14:50:16 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	set_pixel_color(mlx_image_t *img, int x, int y, t_color col)
{
	int	index;

	if (col.a == 0)
		return ;
	index = (y * img->width + x) * 4;
	img->pixels[index + 0] = col.r & 0xFF;
	img->pixels[index + 1] = col.g & 0xFF;
	img->pixels[index + 2] = col.b & 0xFF;
	img->pixels[index + 3] = col.a & 0xFF;
}

static t_color	get_tex_color_at(mlx_texture_t *tex, int x, int y)
{
	int	index;

	if (!tex)
		return ((t_color){0, 0, 0, 0});
	index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (index < 0 || index >= tex->width * tex->height * tex->bytes_per_pixel)
		return ((t_color){0, 0, 0, 0});
	return ((t_color){tex->pixels[index + 0], tex->pixels[index + 1], \
					tex->pixels[index + 2], tex->pixels[index + 3]});
}

static void	draw_column(t_scale start, t_scale end, mlx_texture_t *tex,
	int tex_x)
{
	int		x;
	int		y;
	int		tex_y;
	t_color	color;
	double	multiplier;

	if (end.y <= start.y)
		return ;
	y = fmax(0, start.y) - 1;
	multiplier = (double)tex->height * (tex->width / tex->height) / \
										(end.y - start.y);
	while (y < end.y)
	{
		y++;
		if (y >= game()->mlx->height || y < 0)
			continue ;
		tex_y = (y - start.y) * multiplier;
		color = get_tex_color_at(tex, tex_x, tex_y);
		x = start.x - 1;
		while (++x < end.x && x < game()->mlx->width && x >= 0)
			set_pixel_color(game()->game_scene, x, y, color);
	}
}

void	draw_gameobject(t_range x_range, int height,
	mlx_texture_t *tex, double hit_offset)
{
	int	start_y;
	int	end_y;
	int	x;
	int	texture_x;

	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = start_y + height;
	texture_x = (int)(hit_offset * tex->width) % tex->width;
	x = x_range.min - 1;
	draw_column((t_scale){x, start_y}, (t_scale){x_range.max, end_y}, \
						tex, texture_x);
}
