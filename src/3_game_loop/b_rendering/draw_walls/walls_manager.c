/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:15:34 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/06 17:10:41 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// scale walls calls draw walls
void	do_wall_operations(void)
{
	t_transform	vis_walls[RAYCASTS_PER_DEG * FOV_DEG];
	int			vis_walls_count;

	vis_walls_count = 0;
	write(STDOUT_FILENO, "doing wall operations\n", 22);
	get_visible_walls(vis_walls, &vis_walls_count);
	write(STDOUT_FILENO, "doing wall operations\n", 22);
	quick_sort_walls(vis_walls, 0, vis_walls_count - 1);
	write(STDOUT_FILENO, "doing wall operations\n", 22);
	scale_walls(vis_walls, vis_walls_count);
	write(STDOUT_FILENO, "doing wall operations\n", 22);
	t_wall_scale test = (t_wall_scale){10, 100, 50, 300, 'E'};
	draw_wall(test, game()->game_scene);
}
