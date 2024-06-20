/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/20 04:24:11 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static void	get_x_pixel_from_ray_index(int ray_index, int *start_x, int *end_x)
{
	int		number_of_segments;
	double	segment_width;

	number_of_segments = RAYCASTS_PER_DEG * FOV_DEG;
	segment_width = game()->mlx->width / number_of_segments;
	*start_x = floor((double)ray_index * segment_width);
	*end_x = ceil(((double)ray_index + 1.0) * segment_width);
}

static int	get_height_from_intersection_dist(double intersection_dist)
{
	int		height;

	height = (1.0 / intersection_dist) * (game()->mlx->width / 2) / \
						tan(radians_to_degrees(FOV_DEG) / 2);
	return (abs(height));
}

void	calc_wall(int ray_index, t_vec2 intersect)
{
	int		height;
	int		start_x;
	int		end_x;
	double	player_angle;
	double	ray_angle;

	player_angle = degrees_to_radians(\
						dir_vector_to_degrees(player()->transform.rot));
	ray_angle = player_angle + (ray_index - RAYCASTS_PER_DEG * FOV_DEG / 2) * \
								(M_PI / 180.0 / RAYCASTS_PER_DEG);
	double intersection_dist = pos_distance(player()->transform.pos, intersect);
	printf("intersection_dist: %f\n", intersection_dist);
	double intersection_x = player()->transform.pos.x + intersection_dist * cos(ray_angle);
	double intersection_y = player()->transform.pos.y + intersection_dist * sin(ray_angle);
	double hit_offset;
	if (get_wall_orientation(intersect) == WALL_ORIENTATION_VERTICAL)
		hit_offset = intersection_y - floor(intersection_y);
	else
		hit_offset = intersection_x - floor(intersection_x);
	intersection_dist *= cos(player_angle - ray_angle);
	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(intersection_dist);
	draw_wall_texture(start_x, end_x, height, get_wall_face_to_render(intersect), hit_offset);
}
