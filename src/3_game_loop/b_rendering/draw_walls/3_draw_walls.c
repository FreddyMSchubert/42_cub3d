/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/19 15:10:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
		mlx_put_pixel(img, x, y, col);
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

int	rgba_to_int(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

mlx_texture_t	*get_texture(char d)
{
	if (d == 'N' && game()->no_texture)
		return (game()->no_texture);
	if (d == 'E' && game()->ea_texture)
		return (game()->ea_texture);
	if (d == 'S' && game()->so_texture)
		return (game()->so_texture);
	if (d == 'W' && game()->we_texture)
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

	(void)d;
	texture = get_texture('E'); // N and S dont work
	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = (int)(game()->mlx->height / 2) + height / 2;
	x = start_x;
	while (x != end_x)
	{
		y = start_y;
		while (y < end_y)
		{
			if (!texture)
				set_pixel_color(game()->game_scene, x, y,
					rgba_to_int(255, 0, 255, 255));
			else
			{
				// int repeat = texture->height / texture->width;
				int repeat_y = texture->width / texture->height;
				int texture_x = (int)(hit_offset * texture->width) % texture->width;
				int texture_y = ((y - start_y) * texture->height * repeat_y / (end_y - start_y)) % texture->height;
				int index = (texture_y * texture->width + texture_x) * texture->bytes_per_pixel;
				int color = rgba_to_int(texture->pixels[index], texture->pixels[index + 1], texture->pixels[index + 2], texture->pixels[index + 3]);
				set_pixel_color(game()->game_scene, x, y, color);
			}
			y++;
		}
		if (start_x < end_x)
			x++;
		else
			x--;
	}

}

void	draw_wall(int start_x, int end_x, int height, char d)
{
	int		color;
	int		start_y;
	int		end_y;
	int		y;
	int		x;

	color = get_color(d);
	start_y = (int)(game()->mlx->height / 2) - height / 2;
	end_y = (int)(game()->mlx->height / 2) + height / 2;
	x = start_x;
	while (x != end_x)
	{
		y = start_y;
		while (y < end_y)
		{
			set_pixel_color(game()->game_scene, x, y, color);
			y++;
		}
		if (start_x < end_x)
			x++;
		else
			x--;
	}
}
