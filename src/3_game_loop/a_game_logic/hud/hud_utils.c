/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/25 14:39:16 by jkauker          ###   ########.fr       */
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
				&& y >= 0 && y < (int)(image->height))
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
				&& y >= 0 && y < (int)(image->height))
			{
				mlx_put_pixel(image, x + i, y + j, color);
			}
		}
	}
}

void	draw_square_world(int x, int y, int size, int color)
{
	int			i;
	int			j;
	mlx_image_t	*image;

	image = game()->worldmap;
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

// bool	is_visible(int x, int y)
// {
// 	float	player_rot_x = player()->transform.rot.x;
// 	float	player_rot_y = player()->transform.rot.y;
// 	float	dir_x = x - player()->transform.pos.x;
// 	float	dir_y = y - player()->transform.pos.y;
// 	float	dir_magnitude = sqrt(dir_x * dir_x + dir_y * dir_y);
// 	dir_x /= dir_magnitude;
// 	dir_y /= dir_magnitude;
// 	float	player_rot_magnitude = sqrt(player_rot_x * player_rot_x + player_rot_y * player_rot_y);
// 	player_rot_x /= player_rot_magnitude;
// 	player_rot_y /= player_rot_magnitude;
// 	float	dot_product = dir_x * player_rot_x + dir_y * player_rot_y;
// 	if (acos(dot_product) <= M_PI / 4.5
// 		&& dir_magnitude <= VIEW_DIST * 5)
// 		return (true);
// 	return (false);
// }

t_vec2	normalize_player_rotation(void)
{
	t_vec2	player_rot;
	double	magnitude;

	player_rot.x = player()->transform.rot.x;
	player_rot.y = player()->transform.rot.y;
	magnitude = sqrt(player_rot.x * player_rot.x + player_rot.y * player_rot.y);
	player_rot.x /= magnitude;
	player_rot.y /= magnitude;
	return (player_rot);
}

t_vec2	calculate_normalized_direction(int x, int y)
{
	t_vec2	dir;
	double	magnitude;

	dir.x = x - player()->transform.pos.x;
	dir.y = y - player()->transform.pos.y;
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

	dot_product = dir.x * player_rot.x + dir.y * player_rot.y;
	dir_magnitude = sqrt((x - player()->transform.pos.x)
			* (x - player()->transform.pos.x)
			+ (y - player()->transform.pos.y)
			* (y - player()->transform.pos.y));
	player_rot = normalize_player_rotation();
	dir = calculate_normalized_direction(x, y);
	if (acos(dot_product) <= M_PI / 4.5 && dir_magnitude <= VIEW_DIST * 5)
		return (true);
	return (false);
}
