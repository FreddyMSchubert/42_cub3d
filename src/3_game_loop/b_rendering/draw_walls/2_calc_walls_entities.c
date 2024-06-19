/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/19 16:11:14 by fschuber         ###   ########.fr       */
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

static int	get_height_from_intersection_dist(double intersection_dist)
{
	int		height;

	height = (4.0 / intersection_dist) * (game()->mlx->width / 2) / \
						tan(rad_to_deg(FOV_DEG) / 2);
	return (abs(height));
}

void	calc_wall(int ray_index, double intersection_dist, char d)
{
	int		height;
	int		start_x;
	int		end_x;
	double	player_angle;
	double	ray_angle;

	player_angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot));
	ray_angle = player_angle - deg_to_rad(FOV_DEG / 2.0) + \
							deg_to_rad((double)ray_index / RAYCASTS_PER_DEG);
	intersection_dist *= cos(ray_angle - player_angle);
	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(intersection_dist);
	draw_wall(start_x, end_x, height, d);
}

void	calc_entity(int ray_index, t_entity *ntt, double intersection_dist)
{
	int		height;
	int		start_x;
	int		end_x;
	double	player_angle;
	double	ray_angle;

	player_angle = deg_to_rad(\
						dir_vec_to_deg(player()->transform.rot));
	ray_angle = player_angle + (ray_index - RAYCASTS_PER_DEG * FOV_DEG / 2) * \
								(M_PI / 180.0 / RAYCASTS_PER_DEG);
	intersection_dist *= cos(player_angle - ray_angle);
	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(intersection_dist);
	printf("calc_entity: %d %d %d %d\n", start_x, end_x, height, ntt->type);
	draw_entity(start_x, end_x, height, ntt);
}
