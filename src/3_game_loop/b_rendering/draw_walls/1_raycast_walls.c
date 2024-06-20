/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycast_walls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 06:26:51 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static t_vec2	perform_wall_raycast(int i)
{
	t_transform	ray;
	double		p_angle;
	double		ray_angle;

	p_angle = dir_vec_to_deg(player()->transform.rot);
	ray_angle = p_angle - FOV_DEG / 2.0 + (double)i / (double)RAYCASTS_PER_DEG;
	ray.rot = deg_to_dir_vec(ray_angle);
	ray.rot = scale_vector(ray.rot, VIEW_DIST);
	ray.pos = player()->transform.pos;
	return (get_wall_intersection(game()->input_data->walls, ray));
}

static t_entity	*perform_entity_raycast(int i, t_vec2 *entity_intersection)
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
	*entity_intersection = get_entity_intersection(game()->entities, ray, &entity);
	return (entity);
}

static mlx_texture_t	*get_wall_texture(char d)
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

void	raycast_walls(void)
{
	int			ray_index;
	t_vec2		wall_intersection;
	t_vec2		entity_intersection;
	double		entity_intersection_dist;
	t_entity	*ntt;

	ray_index = -1;
	while (++ray_index < RAYCASTS_PER_DEG * FOV_DEG)
	{
		wall_intersection = perform_wall_raycast(ray_index);
		ntt = perform_entity_raycast(ray_index, &entity_intersection);
		calc_gameobject(ray_index, wall_intersection, get_wall_texture(get_wall_face_to_render(wall_intersection)));
		entity_intersection_dist = pos_distance(player()->transform.pos, entity_intersection);
		if (entity_intersection_dist != -1 && entity_intersection_dist <= VIEW_DIST &&
			ntt != NULL && entity_intersection_dist < pos_distance(player()->transform.pos, wall_intersection))
			calc_gameobject(ray_index, entity_intersection, ntt->texture);
	}
}
