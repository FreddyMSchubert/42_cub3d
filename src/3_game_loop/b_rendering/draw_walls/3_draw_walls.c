/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 03:21:03 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
		mlx_put_pixel(img, x, y, col);
}

static mlx_texture_t	*get_wall_texture(char d)
{
	if (d == 'N')
		return (game()->no_texture);
	if (d == 'E')
		return (game()->ea_texture);
	if (d == 'S')
		return (game()->so_texture);
	if (d == 'W')
		return (game()->we_texture);
	return (NULL);
}

void	draw_wall_texture(int start_x, int end_x, int height, int d, double hit_offset)
{
	mlx_texture_t	*texture;
	int				start_y;
	int				end_y;
	int				y;
	int				x;

	texture = get_wall_texture(d);
	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = (int)(game()->mlx->height / 2) + height / 2;
	x = start_x;
	while (x != end_x)
	{
		y = start_y;
		while (y < end_y)
		{
			int repeat_y = texture->width / texture->height;
			int texture_x = (int)(hit_offset * texture->width) % texture->width;
			int texture_y = ((y - start_y) * texture->height * repeat_y / (end_y - start_y)) % texture->height;
			int index = (texture_y * texture->width + texture_x) * texture->bytes_per_pixel;
			int color = rgba_to_int(texture->pixels[index], texture->pixels[index + 1], texture->pixels[index + 2], texture->pixels[index + 3]);
			set_pixel_color(game()->game_scene, x, y++, color);
		}
		if (start_x < end_x)
			x++;
		else
			x--;
	}

}
