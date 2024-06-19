/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/19 11:37:35 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static double	perform_wall_raycast(int i, char *d)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	double		wall_intersection_dist;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	wall_intersection_dist = wall_ray_dist(game()->input_data->walls, ray, d);
	return (wall_intersection_dist);
}

static t_entity	*perform_entity_raycast(int i, double *entity_intersection_dist)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	t_entity	*entity;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	*entity_intersection_dist = entity_ray_dist(game()->entities, ray, &entity);
	return (entity);
}

void	raycast_walls(void)
{
	int			ray_index;
	double		wall_intersection_dist;
	double		entity_intersection_dist;
	t_entity	*ntt;
	char		d;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		wall_intersection_dist = perform_wall_raycast(ray_index, &d);
		ntt = perform_entity_raycast(ray_index, &entity_intersection_dist);
		if (wall_intersection_dist != -1 && wall_intersection_dist <= VIEW_DIST)
			calc_wall(ray_index, wall_intersection_dist, d);
		if (entity_intersection_dist != -1 && entity_intersection_dist <= VIEW_DIST &&
			ntt != NULL && entity_intersection_dist < wall_intersection_dist)
			calc_entity(ray_index, ntt, entity_intersection_dist);
	}
}
