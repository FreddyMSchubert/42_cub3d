/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:45 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 16:29:09 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	render_game_scene(void)
{
	write(STDOUT_FILENO, "2", 1);
	sort_and_raycast_walls();
	write(STDOUT_FILENO, "2", 1);
	scale_walls();
	write(STDOUT_FILENO, "2", 1);
	draw_walls();
	write(STDOUT_FILENO, "2", 1);
}
