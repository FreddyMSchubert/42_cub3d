/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:23:28 by freddy            #+#    #+#             */
/*   Updated: 2024/06/10 16:07:49 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	print_game_data(void)
{
	if (!TERMINAL_MAP)
		return ;
	printf("\033[2J");
	print_map(game()->input_data->map, ".01");
}

void	loop_hook(void *param)
{
	render_game_scene();
	print_game_data();
	printf("POS: [%f, %f] - ROT: [%f, %f]: %d\n", player()->transform.pos.x, player()->transform.pos.y, player()->transform.rot.x, player()->transform.rot.y, *game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x]);
	(void) param;
}
