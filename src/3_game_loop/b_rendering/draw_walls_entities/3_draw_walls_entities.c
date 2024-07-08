/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/07/08 11:14:44 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// pos is the pixel to draw at
// tex is the pixel of the texture the color is from
static void	set_pixel_color(t_scale pos, t_color col, t_scale tex,
	t_image_data data)
{
	int	index;

	if (col.a == 0)
		return ;
	if (col.a == 38)
		col = get_elementor_cloak_color(tex);
	col = apply_fog(col, data.distance);
	index = (pos.y * data.img->width + pos.x) * 4;
	data.img->pixels[index + 0] = col.r & 0xFF;
	data.img->pixels[index + 1] = col.g & 0xFF;
	data.img->pixels[index + 2] = col.b & 0xFF;
	data.img->pixels[index + 3] = col.a & 0xFF;
}

static t_color	get_tex_color_at(mlx_texture_t *tex, int x, int y)
{
	int		index;
	t_color	col;

	if (!tex)
		return ((t_color){0, 0, 0, 0});
	index = (y * tex->width + x) * tex->bytes_per_pixel;
	if (index < 0 || (uint32_t)index >= \
						tex->width * tex->height * tex->bytes_per_pixel)
		return ((t_color){0, 0, 0, 0});
	col.r = tex->pixels[index + 0];
	col.g = tex->pixels[index + 1];
	col.b = tex->pixels[index + 2];
	col.a = tex->pixels[index + 3];
	return (col);
}

static void	draw_column(t_scale start, t_scale end,
	int tex_x, t_image_data data)
{
	int		x;
	int		y;
	int		tex_y;
	t_color	color;
	double	multiplier;

	if (end.y <= start.y)
		return ;
	y = fmax(0, start.y) - 1;
	multiplier = (double)data.tex->height
		* (data.tex->width / data.tex->height) / (end.y - start.y);
	while (y < end.y)
	{
		y++;
		if (y >= game()->mlx->height || y < 0)
			continue ;
		tex_y = (y - start.y) * multiplier;
		color = get_tex_color_at(data.tex, tex_x, tex_y);
		x = start.x - 1;
		while (++x < end.x && x < game()->mlx->width && x >= 0)
			set_pixel_color((t_scale){x, y}, color, (t_scale){tex_x, tex_y},
				(t_image_data){data.distance, game()->game_scene, NULL});
	}
}

void	draw_gameobject(t_range x_range, int height,
	double hit_offset, t_image_data data)
{
	int	start_y;
	int	end_y;
	int	x;
	int	texture_x;

	if (!data.tex || !data.tex->width)
		cub_exit("No texture to draw", 1);
	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = start_y + height;
	texture_x = (int)(hit_offset * data.tex->width) % data.tex->width;
	x = x_range.min - 1;
	draw_column((t_scale){x, start_y}, (t_scale){x_range.max, end_y},
		texture_x, (t_image_data){data.distance, NULL, data.tex});
}
