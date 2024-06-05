/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/06/05 11:52:17 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_player(void)
{
	printf("Setting pos\n");
	player()->transform.pos.x = player()->spawn_transform.pos.x;
	player()->transform.pos.y = player()->spawn_transform.pos.y;
	player()->transform.rot.x = player()->spawn_transform.rot.x;
	player()->transform.rot.y = player()->spawn_transform.rot.y;
	printf("pos is %f %f\n", player()->transform.pos.x, player()->transform.pos.y);
}
