/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls_entities.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1999/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/04 19:58:34 by freddy           ###   ########.fr       */
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

static int	get_height_from_intersection_dist(double corrected_dist)
{
	int		height;
	double	vertical_fov_rad;

	vertical_fov_rad = 4.1f * atan(tan(rad_to_deg(FOV_DEG) / 2)
			/ (game()->mlx->width / game()->mlx->height));
	height = (game()->mlx->height) / (tan(vertical_fov_rad) * corrected_dist);
	return (abs(height));
}

static double	get_ntt_hit_offset(t_vec2 intersect, t_transform ntt_face)
{
	t_vec2	line_to_point;
	double	dot_product;
	double	line_rot_sqr_mag;

	line_to_point = vec2_sub(intersect, ntt_face.pos);
	dot_product = vec2_dot_product(line_to_point, ntt_face.rot);
	line_rot_sqr_mag = vec2_sqr_magnitude(ntt_face.rot);
	return (dot_product / line_rot_sqr_mag);
}

void	calc_wall(int ray_index, t_vec2 intersect)
{
	int		height;
	t_range	range;
	double	intersection_dist;
	double	angle_correction_rad;

	timing(TIMING_MODE_START, TIMING_TYPE_WALL_CALC);
	get_x_pixel_from_ray_index(ray_index, &range.min, &range.max);
	intersection_dist = pos_dist(player()->transform.pos, intersect);
	angle_correction_rad = \
						deg_to_rad(get_fisheye_corrected_ray_angle(ray_index));
	height = get_height_from_intersection_dist(intersection_dist * \
					cos(angle_correction_rad));
	timing(TIMING_MODE_START, TIMING_TYPE_WALL_DRAW);
	draw_gameobject(range, height, \
			get_wall_texture(get_wall_face_to_render(intersect)), \
							intersect.y - floor(intersect.y) + \
						intersect.x - floor(intersect.x));
	timing(TIMING_MODE_STOP, TIMING_TYPE_WALL_DRAW);
	timing(TIMING_MODE_STOP, TIMING_TYPE_WALL_CALC);
}

void	calc_entity(int ray_index, t_vec2 intersect, t_entity *ntt)
{
	int		height;
	t_range	range;
	double	intersection_dist;
	double	angle_correction_rad;

	timing(TIMING_MODE_START, TIMING_TYPE_NTT_CALC);
	get_x_pixel_from_ray_index(ray_index, &range.min, &range.max);
	intersection_dist = pos_dist(player()->transform.pos, intersect);
	angle_correction_rad = deg_to_rad(\
						get_fisheye_corrected_ray_angle(ray_index));
	height = get_height_from_intersection_dist(intersection_dist * \
						cos(angle_correction_rad));
	timing(TIMING_MODE_START, TIMING_TYPE_NTT_DRAW);
	draw_gameobject(range, height, ntt->get_texture(ntt), \
						get_ntt_hit_offset(intersect, get_face_vector(ntt)));
	timing(TIMING_MODE_STOP, TIMING_TYPE_NTT_DRAW);
	timing(TIMING_MODE_STOP, TIMING_TYPE_NTT_CALC);
}
