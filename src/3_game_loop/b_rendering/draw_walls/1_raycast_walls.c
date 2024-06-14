/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/14 11:10:00 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static double	perform_raycast(int i, char *d)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	double		intersection_dist;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_transform(ray.rot, RENDER_DISTANCE);
	ray.pos = player()->transform.pos;
	intersection_dist = get_ray_distance(game()->input_data->walls, ray, d);
	return (intersection_dist);
}

void	raycast_walls(void)
{
	int			ray_index;
	double		intersection_dist;
	char		d;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		intersection_dist = perform_raycast(ray_index, &d);
		if (intersection_dist == -1 || intersection_dist > RENDER_DISTANCE)
			continue ;
		calc_wall(ray_index, intersection_dist, d);
	}
}
