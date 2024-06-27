/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:47:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 15:47:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
				if (pos_distance(((t_entity *)ntt1->content)->transform.pos, ((t_entity *)ntt2->content)->transform.pos) < DEFAULT_COLLISION_DISTANCE)
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

	ntt_list = game()->entities;
	while (ntt_list)
	{
		((t_entity *)ntt_list->content)->tick((t_entity *)ntt_list->content);
		ntt_list = ntt_list->next;
	}
}
