/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:51:45 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 18:38:24 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_transform	get_face_vector(t_entity *ntt, int id)
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
	dir.x = player(id)->transform.pos.x - ntt->transform.pos.x;
	dir.y = player(id)->transform.pos.y - ntt->transform.pos.y;
	dir = scale_vector(dir, 1);
	face_vector.rot = rotate_vector_by_90_degrees(dir, 1);
	face_vector.pos.x = ntt->transform.pos.x - 0.5 * face_vector.rot.x;
	face_vector.pos.y = ntt->transform.pos.y - 0.5 * face_vector.rot.y;

	return (face_vector);
}

t_entity	*create_entity(t_transform trans, t_entity_type type, mlx_texture_t *tex, bool is_billboard, void (*tick)(t_entity *self))
{
	t_entity	*entity;

	entity = gc_malloc(sizeof(t_entity));
	entity->spawn_transform = trans;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	entity->texture = tex;
	entity->is_billboard = is_billboard;
	entity->tick = tick;
	entity->data = NULL;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
	return (entity);
}

void	delete_entity(t_entity *self)
{
	t_list	**entities;
	t_list	*prev;

	entities = &game()->entities;
	prev = NULL;
	while (*entities)
	{
		if ((*entities)->content == self)
		{
			if (prev) // Not the first element
			{
				prev->next = (*entities)->next;
			}
			else // First element
			{
				game()->entities = (*entities)->next;
			}
			*entities = NULL;
			return;
		}
		prev = *entities;
		entities = &(*entities)->next;
	}
}
