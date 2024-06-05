/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/06/05 11:53:09 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	loop_hook(void *param)
{
	// t_entity	*p;

	// p = player();
	// printf("POS: [%f, %f] - ROT: [%f, %f]: %d\n", p->transform.pos.x, p->transform.pos.y, p->transform.rot.x, p->transform.rot.y, *game()->input_data->map[(int)p->transform.pos.y][(int)p->transform.pos.x]);
	(void) param;
	
}
