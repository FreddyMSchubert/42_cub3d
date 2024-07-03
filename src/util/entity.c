/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:51:45 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 12:17:19 by fschuber         ###   ########.fr       */
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

t_entity	*create_entity(t_transform trans, t_entity_type type, \
		mlx_texture_t	*(*tex)(t_entity *self), void (*tick)(t_entity *self))
{
	t_entity			*entity;
	static unsigned int	id = 0;

	id++;
	entity = malloc(sizeof(t_entity));
	if (!entity)
		cub_exit("Failed to allocate memory for entity", -1);
	entity->id = id;
	entity->spawn_transform = trans;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	entity->get_texture = tex;
	entity->frames_since_state_change = 0;
	entity->is_billboard = true;
	entity->health = INT_MAX;
	entity->tick = tick;
	entity->on_collision = NULL;
	entity->data = NULL;
	entity->to_be_deleted = false;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
	return (entity);
}

void	delete_entity(t_entity *self)
{
	t_list	*entities;
	t_list	*prev;

	entities = game()->entities;
	prev = NULL;
	while (entities)
	{
		if (self->id == ((t_entity *)entities->content)->id)
		{
			if (prev)
				prev->next = entities->next;
			else
				game()->entities = entities->next;
			if (self->data)
				free(self->data);
			free(self);
			free(entities);
			return ;
		}
		prev = entities;
		entities = entities->next;
	}
}

void	drop_orbs(t_transform trans, int element)
{
	t_entity	*ntt;
	t_orb		*orb;

	ntt = create_entity(trans, ORB_NTT, get_texture_orb, tick_orb);
	orb = malloc(sizeof(t_orb));
	orb->element = element;
	ntt->data = orb;
}
