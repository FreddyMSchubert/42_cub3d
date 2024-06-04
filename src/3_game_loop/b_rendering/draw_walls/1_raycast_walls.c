/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/04 12:52:29 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

/*
	1. Shoot raycasts in a bunch of directions, keeping track of the walls they hit in a local array
	2. Sort the walls by distance from the player

	we will not malloc to keep the visible walls, we will just use a local array
	raycasts per deg*fov deg is not actually how logn its gonna be though, its just how long it could possibly be.
	actual amount is saved in vis_walls_count
*/

static t_transform	*perform_raycast(int i)
{
	t_transform	ray;
	t_transform	*intersection;
	double		p_angle;
	double		ray_angle;

	p_angle = dir_vector_to_degrees(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = degrees_to_dir_vector(ray_angle);
	ray.rot = scale_transform(ray.rot, RENDER_DISTANCE);
	ray.pos = player()->transform.pos;
	intersection = get_intersection_wall(game()->input_data->walls, ray);
	return (intersection);
}

void	get_visible_walls(t_transform *vis_walls, int *vis_walls_count)
{
	int			i;
	int			j;
	bool		is_duplicate;
	t_transform	*wall;

	i = -1;
	while (++i < RAYCASTS_PER_DEG * FOV_DEG)
	{
		printf("woohoo i is %d and walls count is %d and fov deg * raycasts per deg is %d\n", i, *vis_walls_count, RAYCASTS_PER_DEG * FOV_DEG);
		wall = perform_raycast(i);
		if (!wall)
			continue ;
		is_duplicate = false;
		j = -1;
		while (++j < *vis_walls_count)
		{
			if (is_same_wall(vis_walls[j], *wall))
			{
				is_duplicate = true;
				break ;
			}
		}
		if (!is_duplicate)
			vis_walls[(*vis_walls_count)++] = *wall;
	}
}
