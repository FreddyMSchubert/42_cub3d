/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 18:21:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_player(int id)
{
	player(id)->transform.pos.x = player(id)->spawn_transform.pos.x + 0.5;
	player(id)->transform.pos.y = player(id)->spawn_transform.pos.y + 0.5;
	player(id)->transform.rot.x = player(id)->spawn_transform.rot.x;
	player(id)->transform.rot.y = player(id)->spawn_transform.rot.y;
}
