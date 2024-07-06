/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_entities.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:27:44 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:16:41 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

t_entity	**perform_entity_raycast(int i, t_vec2 **entity_intersects)
{
	t_trans		ray;
	double		p_angle;
	double		ray_angle;
	t_entity	**entities;

	p_angle = dir_vec_to_deg(player()->trans.rot);
	ray_angle = get_fisheye_corrected_ray_angle(i);
	ray_angle += p_angle;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->trans.pos;
	*entity_intersects = get_entity_intersection(ray, &entities);
	return (entities);
}

static inline double	get_max_dist(t_entity **ntts, \
					t_vec2 *entity_intersects, int count, int *farthest_index)
{
	double		max_dist;
	double		dist;
	int			i;

	max_dist = -1.0;
	*farthest_index = -1;
	i = -1;
	while (++i < count)
	{
		if (ntts[i] == NULL)
			continue ;
		dist = pos_dist(player()->trans.pos, entity_intersects[i]);
		if (dist > max_dist)
		{
			max_dist = dist;
			*farthest_index = i;
		}
	}
	return (max_dist);
}

static inline void	draw_entities_ordered(t_entity **ntts, \
							t_vec2 *entity_intersects, int count, int ray_index)
{
	int		farthest_index;
	int		j;

	j = -1;
	while (++j < count)
	{
		get_max_dist(ntts, entity_intersects, count, &farthest_index);
		if (farthest_index != -1 || RENDER_ENTITIES_THROUGH_WALLS)
		{
			calc_entity(ray_index, entity_intersects[farthest_index], \
									ntts[farthest_index]);
			ntts[farthest_index] = NULL;
		}
	}
}

void	start_calc_entities(t_entity **ntts, \
					t_vec2 *entity_intersects, double wall_dist, int ray_index)
{
	int			j;
	int			count;

	count = 0;
	while (ntts[count])
		count++;
	j = -1;
	while (++j < count)
		if (pos_dist(player()->trans.pos, entity_intersects[j]) > wall_dist)
			ntts[j] = NULL;
	draw_entities_ordered(ntts, entity_intersects, count, ray_index);
	free(ntts);
	free(entity_intersects);
}
