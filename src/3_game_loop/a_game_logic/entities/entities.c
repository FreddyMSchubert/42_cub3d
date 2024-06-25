/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:47:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 11:48:32 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
