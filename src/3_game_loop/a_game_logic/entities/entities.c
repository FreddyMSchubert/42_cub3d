/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:47:39 by freddy            #+#    #+#             */
/*   Updated: 2024/07/05 21:28:23 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define PROJECTILE_PLAYER_COLLISION_DISTANCE 0.1

static inline bool	check_colliding(t_transform t1, t_transform t2)
{
	t_vec2	pos1;
	t_vec2	pos2;

	t1.rot = scale_vector(t1.rot, 1);
	pos1.x = t1.pos.x - (t1.rot.x * 0.5);
	pos1.y = t1.pos.y - (t1.rot.y * 0.5);
	t2.rot = scale_vector(t2.rot, 1);
	pos2.x = t2.pos.x - (t2.rot.x * 0.5);
	pos2.y = t2.pos.y - (t2.rot.y * 0.5);
	return (pos_dist(pos1, pos2) < DEFAULT_COLLISION_DISTANCE);
}

static inline void	alert_colliding(t_entity *e1, t_entity *e2)
{
	if (e1->id == e2->id)
		return ;
	if (!check_colliding(get_face_vector(e1), get_face_vector(e2)))
		return ;
	if (e1->on_collision)
		e1->on_collision(e1, e2);
	if (e2->on_collision)
		e2->on_collision(e2, e1);
}

void	collide_entities(void)
{
	t_list	*ntt1;
	t_list	*ntt2;

	ntt1 = game()->entities;
	while (ntt1)
	{
		ntt2 = ntt1->next;
		while (ntt2)
		{
			alert_colliding((t_entity *)ntt1->content, \
							(t_entity *)ntt2->content);
			ntt2 = ntt2->next;
		}
		if (check_colliding(player()->transform, \
						((t_entity *)ntt1->content)->transform))
			on_collision_player((t_entity *)ntt1->content);
		ntt1 = ntt1->next;
	}
}

void	tick_entities(void)
{
	t_list		*ntt_list;
	t_entity	*ntt;

	ntt_list = game()->entities;
	while (ntt_list)
	{
		ntt = (t_entity *)ntt_list->content;
		ntt->tick((t_entity *)ntt_list->content);
		ntt_list = ntt_list->next;
	}
	ntt_list = game()->entities;
	if (ntt_list && ((t_entity *)ntt_list->content)->to_be_deleted)
		delete_entity((t_entity *)ntt_list->content);
	ntt_list = game()->entities;
	while (ntt_list && ntt_list->next)
	{
		if (((t_entity *)ntt_list->next->content)->to_be_deleted)
			delete_entity((t_entity *)ntt_list->next->content);
		ntt_list = ntt_list->next;
	}
}
