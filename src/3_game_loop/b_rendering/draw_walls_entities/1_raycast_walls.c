/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:16:23 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static inline t_vec2	perform_wall_raycast(int ray_index)
{
	t_trans		ray;
	double		p_angle_deg;
	double		angle_correction;
	double		ray_angle_deg;

	p_angle_deg = dir_vec_to_deg(player()->trans.rot);
	angle_correction = get_fisheye_corrected_ray_angle(ray_index);
	ray_angle_deg = p_angle_deg + angle_correction;
	ray.rot = deg_to_dir_vec(ray_angle_deg);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->trans.pos;
	return (get_wall_intersection(game()->input_data->walls, ray));
}

void	raycast_walls(void)
{
	int			ray_index;
	t_vec2		wall_intersect;
	t_vec2		*entity_intersects;
	t_entity	**ntts;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		timing(TIMING_MODE_START, TIMING_TYPE_WALL_RAYCAST);
		wall_intersect = perform_wall_raycast(ray_index);
		calc_wall(ray_index, wall_intersect);
		timing(TIMING_MODE_STOP, TIMING_TYPE_WALL_RAYCAST);
		timing(TIMING_MODE_START, TIMING_TYPE_NTT_RAYCAST);
		ntts = perform_entity_raycast(ray_index, &entity_intersects);
		start_calc_entities(ntts, entity_intersects, \
				pos_dist(player()->trans.pos, wall_intersect), ray_index);
		timing(TIMING_MODE_STOP, TIMING_TYPE_NTT_RAYCAST);
	}
}
