/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/06/05 18:54:53 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	loop_hook(void *param)
{
	render_game_scene();
	printf("POS: [%f, %f] - ROT: [%f, %f]: %d\n", player()->transform.pos.x, player()->transform.pos.y, player()->transform.rot.x, player()->transform.rot.y, *game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x]);
	(void) param;
	
}
