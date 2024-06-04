/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_sort_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/04 09:53:16 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

/*
	1. Shoot raycasts in a bunch of directions, keeping track of the walls they hit in a local array
	2. Sort the walls by distance from the player

	we will not malloc to keep the visible walls, we will just use a local array
	raycasts per deg*fov deg is not actually how logn its gonna be though, its just how long it could possibly be.
	actual amount is saved in visible_walls_count
*/

static t_transform	*perform_raycast(int i)
{
	t_transform	ray;
	t_vec2		*intersection;
	double		p_angle;
	double		ray_angle;

	p_angle = dir_vector_to_degrees(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = degrees_to_dir_vector(ray_angle);
	ray.pos = player()->transform.pos;
	intersection = get_intersection_wall(data()->input_data->walls, ray);
	return (intersection);
}

static void	get_visible_walls(t_transform *visible_walls, int *visible_walls_count)
{
	int		i;

	i = -1;
	while (++i < RAYCASTS_PER_DEG * FOV_DEG)
	{
		// shoot raycast
		// if it hits a wall, add it to visible_walls
		// increment i
	}
}

void	sort_and_raycast_walls(void)
{
	t_transform	visible_walls[RAYCASTS_PER_DEG * FOV_DEG];
	int			visible_walls_count;

	data()->raycasted_sorted_walls = data()->input_data->walls;
	// clear image
	mlx_image_t	*img = data()->game_scene;
	if (img && img->pixels && img->width > 0 && img->height > 0)
		for (int i = 0; i < (int)(img->width * img->height); i++)
			img->pixels[i] = 0;
}
