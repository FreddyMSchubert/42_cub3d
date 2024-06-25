/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1999/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/25 18:59:37 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

double	get_fisheye_corrected_ray_angle(int ray_index);

static void	get_x_pixel_from_ray_index(int ray_index, int *start_x, int *end_x, int id)
{
	int		number_of_segments;
	double	segment_width;

	number_of_segments = RAYCASTS_PER_DEG * FOV_DEG;
	segment_width = (double)player(id)->mlx->width / number_of_segments;
	*start_x = (int)((double)ray_index * segment_width);
	*end_x = (int)(((double)ray_index + 1) * segment_width);
	if (ray_index == number_of_segments - 1)
		*end_x = player(id)->mlx->width;
}

static int	get_height_from_intersection_dist(double corrected_dist, int id)
{
	int		height;
	double	vertical_fov_rad;

	vertical_fov_rad = 4.1f * atan(tan(rad_to_deg(FOV_DEG) / 2)
			/ (player(id)->mlx->width / player(id)->mlx->height));
	height = (player(id)->mlx->height) / (tan(vertical_fov_rad) * corrected_dist);
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

static inline mlx_texture_t	*get_wall_texture(char d)
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

void	calc_wall(int ray_index, t_vec2 intersect, int id)
{
	int		height;
	int		start_x;
	int		end_x;
	double	hit_offset;
	double	intersection_dist;
	double	corrected_dist;
	double	angle_correction_rad;

	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x, id);
	intersection_dist = pos_distance(player(id)->transform.pos, intersect);
	angle_correction_rad = deg_to_rad(get_fisheye_corrected_ray_angle(ray_index));
	corrected_dist = intersection_dist * cos(angle_correction_rad);
	height = get_height_from_intersection_dist(corrected_dist, id);
	hit_offset = intersect.y - floor(intersect.y) + \
						intersect.x - floor(intersect.x);
	draw_gameobject(start_x, end_x, height, \
			get_wall_texture(get_wall_face_to_render(intersect, id)), hit_offset, id);
}

void	calc_entity(int ray_index, t_vec2 intersect, t_entity *ntt, int id)
{
	int		height;
	int		start_x;
	int		end_x;
	double	hit_offset;
	double	intersection_dist;
	double	corrected_dist;
	double	angle_correction_rad;

	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x, id);
	intersection_dist = pos_distance(player(id)->transform.pos, intersect);
	angle_correction_rad = deg_to_rad(get_fisheye_corrected_ray_angle(ray_index));
	corrected_dist = intersection_dist * cos(angle_correction_rad);
	height = get_height_from_intersection_dist(corrected_dist, id);
	hit_offset = get_ntt_hit_offset(intersect, get_face_vector(ntt, id));
	draw_gameobject(start_x, end_x, height, ntt->texture, hit_offset, id);
}