/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:28:05 by freddy            #+#    #+#             */
/*   Updated: 2024/05/29 09:20:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_player(void)
{
	printf("Setting pos\n");
	get_player()->transform.pos.x = get_player()->spawn_transform.pos.x;
	get_player()->transform.pos.y = get_player()->spawn_transform.pos.y;
	get_player()->transform.rot.x = get_player()->spawn_transform.rot.x;
	get_player()->transform.rot.y = get_player()->spawn_transform.rot.y;
	printf("pos is %f %f\n", get_player()->transform.pos.x, get_player()->transform.pos.y);
}
