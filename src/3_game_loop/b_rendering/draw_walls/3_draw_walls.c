/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 13:45:43 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static inline void	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (int_to_t_color(col).a == 0)
		return ;
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
		mlx_put_pixel(img, x, y, col);
}

static inline int	get_tex_color_at(mlx_texture_t *tex, int x, int y)
{
	int	index;

	index = (y * tex->width + x) * tex->bytes_per_pixel;
	return (rgba_to_int(tex->pixels[index], tex->pixels[index + 1], \
					tex->pixels[index + 2], tex->pixels[index + 3]));
}

static inline void	draw_column(t_scale start, int end_y, mlx_texture_t *tex,
	int tex_x, int repeat_y)
{
	int	y;
	int	tex_y;
	int	color;

	y = start.y;
	while (y < end_y)
	{
		tex_y = (y - start.y) * tex->height * repeat_y
			/ (end_y - start.y) & (tex->height - 1);
		color = get_tex_color_at(tex, tex_x, tex_y);
		set_pixel_color(game()->game_scene, start.x, y++, color);
	}
}

void	draw_gameobject(int start_x, int end_x, int height,
	mlx_texture_t *tex, double hit_offset)
{
	int				start_y;
	int				end_y;
	int				repeat_y;
	int				x;
	int				texture_x;

	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = start_y + height;
	x = start_x;
	repeat_y = tex->width / tex->height;
	while (x != end_x)
	{
		texture_x = (int)(hit_offset * tex->width) % tex->width;
		draw_column((t_scale){x, start_y}, end_y, tex, texture_x, repeat_y);
		if (start_x < end_x)
			x++;
		else
			x--;
	}
}
