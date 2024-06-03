/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/03 10:59:54 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
		memcpy(&(img->pixels[(y * img->width + x) * sizeof(int32_t)]), \
						&col, sizeof(col));
}

static int	interpolate(int start, int end, int step, int max_steps)
{
	if (max_steps == 0) return start;
	return (start + (end - start) * step / max_steps);
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

static void	draw_wall(t_wall_scale *wall, mlx_image_t *img)
{
	int	col;
	int	x;
	int	y;
	int	current_height;
	int	center_y;
	int	start_y;
	int	end_y;

	if (wall->x_left >= wall->x_right || (wall->height_left == 0  && wall->height_right == 0))
		return ;
	col = get_color(wall->direction);
	printf("Wall from x %d to %d, left: %d, right: %d, col: %08X\n", wall->x_left, wall->x_right, wall->height_left, wall->height_right, col);
	center_y = img->height / 2;
	x = -1;
	while (++x <= wall->x_right - wall->x_left)
	{
		current_height = interpolate(wall->height_left, wall->height_right, x, wall->x_right - wall->x_left);
		start_y = center_y - current_height / 2;
		end_y = center_y + current_height / 2;
		y = start_y - 1;
		while (++y <= end_y)
			set_pixel_color(img, wall->x_left + x, y, col);
	}
}

void	draw_walls(void)
{
	t_wall_scale	**walls;
	mlx_image_t		*img;
	int				i;

	walls = get_persistent_data()->walls_scaled;
	img = get_persistent_data()->game_scene;
	i = -1;
	while (walls && walls[++i])
		draw_wall(walls[i], img);
}
