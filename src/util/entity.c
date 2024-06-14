/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:40:08 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/14 10:50:08 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	create_entity(t_vec2 pos, t_vec2 rot, t_entity_type type)
{
	t_entity	*entity;

	entity = gc_malloc(sizeof(t_entity));
	entity->spawn_transform.pos = pos;
	entity->spawn_transform.rot = rot;
	entity->transform = entity->spawn_transform;
	entity->type = type;
	ft_lstadd_back(&game()->entities, ft_lstnew(entity));
}
