/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1999/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/20 07:34:40 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	get_x_pixel_from_ray_index(int ray_index, int *start_x, int *end_x)
{
	int		number_of_segments;
	double	segment_width;

	number_of_segments = RAYCASTS_PER_DEG * FOV_DEG;
	segment_width = (double)game()->mlx->width / number_of_segments;
	*start_x = (int)((double)ray_index * segment_width);
	*end_x = (int)(((double)ray_index + 1) * segment_width);
	if (ray_index == number_of_segments - 1)
		*end_x = game()->mlx->width;
}

static int	get_height_from_intersection_dist(int ray_index, t_vec2 intersect)
{
	double	intersection_dist;
	double	player_angle;
	double	ray_angle;
	int		height;

	intersection_dist = pos_distance(player()->transform.pos, intersect);
	player_angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot));
	ray_angle = player_angle + (ray_index - RAYCASTS_PER_DEG * FOV_DEG / 2) * \
								(M_PI / 180.0 / RAYCASTS_PER_DEG);
	intersection_dist *= cos(player_angle - ray_angle);
	height = (4.0 / intersection_dist) * (game()->mlx->width / 2) / \
						tan(rad_to_deg(FOV_DEG) / 2);
	return (abs(height));
}

void	calc_gameobject(int ray_index, t_vec2 intersect, mlx_texture_t *tex)
{
	int		height;
	int		start_x;
	int		end_x;
	double	hit_offset;

	write(STDOUT_FILENO, "calc_gameobject\n", 16);
	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(ray_index, intersect);
	hit_offset = intersect.y - floor(intersect.y) + intersect.x - floor(intersect.x);
	draw_gameobject(start_x, end_x, height, tex, hit_offset);
}
