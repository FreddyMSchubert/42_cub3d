/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/05/29 09:08:54 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	loop_hook(void *param)
{
	t_entity	*p;

	p = get_player();
	printf("POS: [%f, %f] - ROT: [%f, %f]: %d\n", p->transform.pos.x, p->transform.pos.y, p->transform.rot.x, p->transform.rot.y, *get_persistent_data()->input_data->map[(int)p->transform.pos.y][(int)p->transform.pos.x]);
	(void) param;
}
