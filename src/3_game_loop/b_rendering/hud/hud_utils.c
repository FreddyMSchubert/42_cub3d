/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/08 11:49:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	draw_square_hud(int x, int y, int size, int color)
{
	int			i;
	int			j;
	mlx_image_t	*image;

	image = game()->hud;
	if (!image)
		return ;
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (x >= 0 && x < (int)(image->width)
				&& y >= 0 && y < (int)(image->height)
				&& (uint32_t)y < game()->hud->height
				&& (uint32_t)x < game()->hud->width)
			{
				mlx_put_pixel(image, x + i, y + j, color);
			}
		}
	}
}

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
				&& y >= 0 && y < (int)(image->height)
				&& (u_int32_t)y < game()->game_scene->height
				&& (u_int32_t)x < game()->game_scene->width)
			{
				mlx_put_pixel(image, x + i, y + j, color);
			}
		}
	}
}

t_vec2	normalize_player_rotation(void)
{
	t_vec2	player_rot;
	double	magnitude;

	player_rot.x = player()->trans.rot.x;
	player_rot.y = player()->trans.rot.y;
	magnitude = sqrt(player_rot.x * player_rot.x + player_rot.y * player_rot.y);
	player_rot.x /= magnitude;
	player_rot.y /= magnitude;
	return (player_rot);
}

t_vec2	calculate_normalized_direction(int x, int y)
{
	t_vec2	dir;
	double	magnitude;

	dir.x = x - player()->trans.pos.x;
	dir.y = y - player()->trans.pos.y;
	magnitude = sqrt(dir.x * dir.x + dir.y * dir.y);
	dir.x /= magnitude;
	dir.y /= magnitude;
	return (dir);
}

bool	is_visible(int x, int y)
{
	t_vec2	dir;
	t_vec2	player_rot;
	float	dot_product;
	float	dir_magnitude;

	player_rot = normalize_player_rotation();
	dir = calculate_normalized_direction(x, y);
	dot_product = dir.x * player_rot.x + dir.y * player_rot.y;
	dir_magnitude = sqrt((x - player()->trans.pos.x)
			* (x - player()->trans.pos.x)
			+ (y - player()->trans.pos.y)
			* (y - player()->trans.pos.y));
	if (acos(dot_product) <= M_PI / 4.5 && dir_magnitude <= VIEW_DIST * 5)
		return (true);
	return (false);
}
