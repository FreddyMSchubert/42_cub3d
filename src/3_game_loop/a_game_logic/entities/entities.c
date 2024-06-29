/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:47:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/29 19:40:01 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline bool	check_colliding(t_entity *ent1, t_entity *ent2)
{
	t_vec2	pos1;
	t_vec2	pos2;

	ent1->transform.rot = scale_vector(ent1->transform.rot, 1);
	pos1.x = ent1->transform.pos.x + ent1->transform.rot.x * 0.5;
	pos1.y = ent1->transform.pos.y + ent1->transform.rot.y * 0.5;
	ent2->transform.rot = scale_vector(ent2->transform.rot, 1);
	pos2.x = ent2->transform.pos.x + ent2->transform.rot.x * 0.5;
	pos2.y = ent2->transform.pos.y + ent2->transform.rot.y * 0.5;
	return (pos_distance(pos1, pos2) < DEFAULT_COLLISION_DISTANCE);
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
			if (ntt1 != ntt2)
			{
				if (check_colliding((t_entity *)ntt1->content, (t_entity *)ntt2->content))
				{
					if (((t_entity *)ntt1->content)->on_collision)
						((t_entity *)ntt1->content)->on_collision((t_entity *)ntt1->content, (t_entity *)ntt2->content);
					if (((t_entity *)ntt2->content)->on_collision)
						((t_entity *)ntt2->content)->on_collision((t_entity *)ntt2->content, (t_entity *)ntt1->content);
				}
			}
			ntt2 = ntt2->next;
		}
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
