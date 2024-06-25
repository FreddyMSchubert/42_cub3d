/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:51:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 11:46:16 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_transform	get_face_vector(t_entity *ntt)
{
	t_transform		face_vector;
	t_vec2			dir;

	if (!ntt->is_billboard)
	{
		face_vector.pos.x = ntt->transform.pos.x - 0.5 * ntt->transform.rot.x;
		face_vector.pos.y = ntt->transform.pos.y - 0.5 * ntt->transform.rot.y;
		face_vector.rot = ntt->transform.rot;
		return (face_vector);
	}
	dir.x = player()->transform.pos.x - ntt->transform.pos.x;
	dir.y = player()->transform.pos.y - ntt->transform.pos.y;
	dir = scale_vector(dir, 1);
	face_vector.rot = rotate_vector_by_90_degrees(dir, 1);
	face_vector.pos.x = ntt->transform.pos.x - 0.5 * face_vector.rot.x;
	face_vector.pos.y = ntt->transform.pos.y - 0.5 * face_vector.rot.y;

	return (face_vector);
}

t_entity	*create_entity(t_vec2 pos, t_vec2 rot, t_entity_type type, mlx_texture_t *tex, bool is_billboard)
{
	t_entity	*entity;

	entity = gc_malloc(sizeof(t_entity));
	entity->spawn_transform.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	entity->spawn_transform.rot = rot;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	entity->texture = tex;
	entity->is_billboard = is_billboard;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
	return (entity);
}
