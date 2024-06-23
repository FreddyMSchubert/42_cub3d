/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_calc_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1999/06/13 09:10:15 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/23 10:24:23 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static inline void	get_x_pixel_from_ray_index(int ray_index, int *start_x, int *end_x)
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

static inline int	get_height_from_intersection_dist(t_vec2 intersect)
{
	double	intersection_dist;
	int		height;

	intersection_dist = pos_distance(player()->transform.pos, intersect);
	height = (4.0 / intersection_dist) * (game()->mlx->width / 2) / \
						tan(rad_to_deg(FOV_DEG) / 2);
	return (abs(height));
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

void	calc_gameobject(int ray_index, t_vec2 intersect)
{
	int		height;
	int		start_x;
	int		end_x;
	double	hit_offset;

	get_x_pixel_from_ray_index(ray_index, &start_x, &end_x);
	height = get_height_from_intersection_dist(intersect);
	hit_offset = intersect.y - floor(intersect.y) + \
						intersect.x - floor(intersect.x);
	draw_gameobject(start_x, end_x, height, \
			get_wall_texture(get_wall_face_to_render(intersect)), hit_offset);
}
