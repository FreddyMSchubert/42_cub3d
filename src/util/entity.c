/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:40:08 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/14 12:51:45 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	create_entity(t_vec2 pos, t_vec2 rot, t_entity_type type)
{
	t_entity	*entity;

	entity = gc_malloc(sizeof(t_entity));
	entity->spawn_transform.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	entity->spawn_transform.rot = rot;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
}

// calculates where the entity should be drawn based on their pos
// and the player's rotation
t_transform	get_face_vector(t_vec2 pos)
{
	t_transform	result;
	double		face_angle;

	face_angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot)) + M_PI / 2;
	result.rot = deg_to_dir_vec(rad_to_deg(face_angle));
	result.rot = scale_transform(result.rot, 1);
	result.pos = (t_vec2){pos.x - result.rot.x / 2, pos.y - result.rot.y / 2};
	return (result);
}
