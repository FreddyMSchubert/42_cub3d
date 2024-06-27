/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 19:27:17 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

double	get_fisheye_corrected_ray_angle(int ray_index)
{
	double	relative_position;
	double	angle_correction;

	relative_position = ((double)ray_index / ((RAYCASTS_PER_DEG * FOV_DEG) / 2)) - 1;
	angle_correction = atan(relative_position * tan(deg_to_rad(FOV_DEG / 2)));
	return (rad_to_deg(angle_correction));
}

static t_entity	**perform_entity_raycast(int i, t_vec2 **entity_intersects)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;
	t_entity	**entities;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = get_fisheye_corrected_ray_angle(i);
	ray_angle += p_angle;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	*entity_intersects = get_entity_intersection(ray, &entities);
	return (entities);
}

static inline t_vec2	perform_wall_raycast(int ray_index)
{
	t_transform	ray;
	double		p_angle_deg;
	double		angle_correction;
	double		ray_angle_deg;

	p_angle_deg = dir_vec_to_deg(player()->transform.rot);
	angle_correction = get_fisheye_corrected_ray_angle(ray_index);
	ray_angle_deg = p_angle_deg + angle_correction;
	ray.rot = deg_to_dir_vec(ray_angle_deg);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	return (get_wall_intersection(game()->input_data->walls, ray));
}

void	start_calc_entities(t_entity **ntts, t_vec2 *entity_intersects, double wall_dist, int ray_index)
{
	double		dist;
	int			i;
	int			j;
	int			farthest_index;
	double		max_dist;
	int			count;

	count = 0;
	while (ntts[count])
		count++;
	j = -1;
	while (++j < count)
		if (pos_distance(player()->transform.pos, entity_intersects[j]) > wall_dist)
			ntts[j] = NULL;
	j = -1;
	while (++j < count)
	{
		max_dist = -1.0;
		farthest_index = -1;
		i = -1;
		while (++i < count)
		{
			if (ntts[i] == NULL)
				continue ;
			dist = pos_distance(player()->transform.pos, entity_intersects[i]);
			if (dist > max_dist)
			{
				max_dist = dist;
				farthest_index = i;
			}
		}
		if (farthest_index != -1 || RENDER_ENTITIES_THROUGH_WALLS)
		{
			calc_entity(ray_index, entity_intersects[farthest_index], ntts[farthest_index]);
			ntts[farthest_index] = NULL;
		}
	}
	free (ntts);
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
		wall_intersect = perform_wall_raycast(ray_index);
		calc_wall(ray_index, wall_intersect);
		ntts = perform_entity_raycast(ray_index, &entity_intersects);
		start_calc_entities(ntts, entity_intersects, pos_distance(player()->transform.pos, wall_intersect), ray_index);
	}
}
