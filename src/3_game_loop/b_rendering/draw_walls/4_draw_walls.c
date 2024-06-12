/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_draw_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:58:47 by freddy            #+#    #+#             */
/*   Updated: 2024/06/12 14:22:00 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static bool	set_pixel_color(mlx_image_t *img, int x, int y, int col)
{
	if (x >= 0 && x < (int)(img->width) && y >= 0 && y < (int)(img->height))
	{
		mlx_put_pixel(img, x, y, col);
		return (true);
	}
	return (false);
}

static int	interpolate(int start, int end, int step, int max_steps)
{
	if (max_steps <= 0)
		return (start);
	if (step < 0)
		step = 0;
	if (step >= max_steps)
		step = max_steps - 1;
	return (start + (end - start) * ((double)step / max_steps));
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

void	draw_wall(t_wall_scale wall, mlx_image_t *img)
{
	int	x;
	int	y;
	int	current_height;
	int	end_y;
	int	pixels_drawn;

	x = -1;
	pixels_drawn = 0;
	// printf("Width: %d - Color: %06X - ", wall.x_right - wall.x_left, get_color(wall.direction));
	while (++x <= wall.x_right - wall.x_left)
	{
		current_height = interpolate(wall.height_left, wall.height_right, x, wall.x_right - wall.x_left);
		y = (img->height / 2) - (current_height / 2);
		if (y < 0)
			y = 0;
		end_y = (img->height / 2) + (current_height / 2);
		if (end_y > (int)(img->height))
			end_y = img->height;
		while (++y <= end_y)
		{
			if (set_pixel_color(img, wall.x_left + x, y, get_color(wall.direction)))
				pixels_drawn++;
		}
	}
	// if (pixels_drawn == 0)
	// 	printf("\t%sERROR%s: No pixels drawn\n", ANSI_COLOR_RED, ANSI_RESET);
	// else
	// 	printf("\t%sSUCCESS%s: Pixels drawn: %d\n", ANSI_COLOR_GREEN, ANSI_RESET, pixels_drawn);
}
