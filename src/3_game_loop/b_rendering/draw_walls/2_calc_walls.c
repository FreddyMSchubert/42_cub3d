/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/13 09:23:39 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static int	get_x_pixel_from_ray_index(int ray_index)
{
	int		x_pos;

	x_pos = ray_index % (RAYCASTS_PER_DEG * FOV_DEG);
	return (x_pos);
}

static int	get_height_from_intersection_dist(double intersection_dist)
{
	int		height;

	height = (int)(RENDER_DISTANCE / intersection_dist);
	return (height);
}

void	calc_wall(int ray_index, double intersection_dist, char d)
{
	int		x_pixel;
	int		height;

	x_pixel = get_x_pixel_from_ray_index(ray_index);
	height = get_height_from_intersection_dist(intersection_dist);
	draw_wall(x_pixel, height, d);
}
