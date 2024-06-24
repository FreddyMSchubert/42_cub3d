/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:51:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 13:25:01 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_transform	get_face_vector(t_transform *ntt_trans)
{
	t_transform		face_vector;
	t_vec2			dir;

	// face the dir towards the player
	dir.x = player()->transform.pos.x - ntt_trans->pos.x;
	dir.y = player()->transform.pos.y - ntt_trans->pos.y;
	dir = scale_vector(dir, 1);

	// turn by 90 degrees
	face_vector.rot = rotate_vector_by_90_degrees(dir, 1);

	// set pos
	face_vector.pos.x = ntt_trans->pos.x - 0.5 * face_vector.rot.x;
	face_vector.pos.y = ntt_trans->pos.y - 0.5 * face_vector.rot.y;

	return (face_vector);
}

void	create_entity(t_vec2 pos, t_vec2 rot, t_entity_type type, mlx_texture_t *tex)
{
	t_entity	*entity;

	entity = gc_malloc(sizeof(t_entity));
	entity->spawn_transform.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	entity->spawn_transform.rot = rot;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	entity->texture = tex;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
}
