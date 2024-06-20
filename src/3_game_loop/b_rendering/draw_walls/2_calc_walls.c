/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/20 05:22:08 by fschuber         ###   ########.fr       */
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

static int	get_height_from_intersection_dist(int ray_index, t_vec2 intersect)
{
	double	intersection_dist;
	double	player_angle;
	double	ray_angle;
	int		height;

	intersection_dist = pos_distance(player()->transform.pos, intersect);
	player_angle = degrees_to_radians(dir_vector_to_degrees(player()->transform.rot));
	ray_angle = player_angle + (ray_index - RAYCASTS_PER_DEG * FOV_DEG / 2) * \
								(M_PI / 180.0 / RAYCASTS_PER_DEG);
	intersection_dist *= cos(player_angle - ray_angle);
	height = (1.0 / intersection_dist) * (game()->mlx->width / 2) / \
						tan(radians_to_degrees(FOV_DEG) / 2);
	return (abs(height));
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

void	calc_wall(int ray_index, t_vec2 intersect)
{
	int		height;
	int		start_x;
	int		end_x;
	double	hit_offset;

	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(ray_index, intersect);
	hit_offset = intersect.y - floor(intersect.y) + intersect.x - floor(intersect.x);
	draw_wall_texture(start_x, end_x, height, get_wall_texture(get_wall_face_to_render(intersect)), hit_offset);
}
