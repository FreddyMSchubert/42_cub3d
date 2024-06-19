/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/19 14:01:13 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static double	perform_raycast(int i, char *d, char *wall_orientation)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	double		intersection_dist;

	p_angle = dir_vector_to_degrees(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = degrees_to_dir_vector(ray_angle);
	ray.rot = scale_transform(ray.rot, RENDER_DISTANCE);
	ray.pos = player()->transform.pos;
	intersection_dist = get_ray_distance(game()->input_data->walls, ray, d, wall_orientation);
	return (intersection_dist);
}

void	raycast_walls(void)
{
	int			ray_index;
	double		intersection_dist;
	char		d;
	char		wall_orientation;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		intersection_dist = perform_raycast(ray_index, &d, &wall_orientation);
		if (intersection_dist == -1 || intersection_dist > RENDER_DISTANCE)
			continue ;
		calc_wall(ray_index, intersection_dist, d, wall_orientation);
	}
}
