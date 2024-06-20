/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 05:15:45 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static t_vec2	perform_raycast(int i)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;

	p_angle = dir_vector_to_degrees(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = degrees_to_dir_vector(ray_angle);
	ray.rot = scale_transform(ray.rot, RENDER_DISTANCE);
	ray.pos = player()->transform.pos;
	return (get_wall_intersection(game()->input_data->walls, ray));
}

void	raycast_walls(void)
{
	int			ray_index;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
		calc_wall(ray_index, perform_raycast(ray_index));
}
