/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 11:58:50 by fschuber         ###   ########.fr       */
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
	if (player()->inv.water_orbs == -1)
		player()->inv.water_orbs = 0;
	if (player()->inv.fire_orbs == -1)
		player()->inv.fire_orbs = 0;
	if (player()->inv.earth_orbs == -1)
		player()->inv.earth_orbs = 0;
	if (player()->inv.air_orbs == -1)
		player()->inv.air_orbs = 0;
	player()->inv.num_available_items = 5;
	player()->inv.current_index = 0;
	player()->inv.text_amount_earth = NULL;
	player()->inv.text_amount_fire = NULL;
	player()->inv.text_amount_water = NULL;
	player()->inv.text_amount_air = NULL;
	if (player()->health == -1)
		player()->health = PLAYER_STARTING_HEALTH;
	if (INFINITE_HEALTH)
		player()->health = INT_MAX / 2;
	player()->element = random_int(0, 3);
}
