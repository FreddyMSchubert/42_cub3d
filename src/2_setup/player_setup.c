/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 15:16:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_player(void)
{
	player()->transform.pos.x = player()->spawn_transform.pos.x + 0.5;
	player()->transform.pos.y = player()->spawn_transform.pos.y + 0.5;
	player()->transform.rot.x = player()->spawn_transform.rot.x;
	player()->transform.rot.y = player()->spawn_transform.rot.y;
	player()->inv.keys = 0;
	player()->inv.water_orbs = 0;
	player()->inv.fire_orbs = 0;
	player()->inv.earth_orbs = 0;
	player()->inv.air_orbs = 0;
	player()->inv.num_available_items = 5;
	player()->inv.current_index = 0;
}
