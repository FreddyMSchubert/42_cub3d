/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 07:16:22 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_player(void)
{
	player()->transform.pos.x = player()->spawn_transform.pos.x + 0.5;
	player()->transform.pos.y = player()->spawn_transform.pos.y + 0.5;
	player()->transform.rot.x = player()->spawn_transform.rot.x;
	player()->transform.rot.y = player()->spawn_transform.rot.y;
}
