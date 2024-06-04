/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:15:34 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/04 11:25:23 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	do_wall_operations(void)
{
	t_transform	vis_walls[RAYCASTS_PER_DEG * FOV_DEG];
	int			vis_walls_count;

	write(STDOUT_FILENO, "1\n", 2);
	get_visible_walls(vis_walls, &vis_walls_count);
	write(STDOUT_FILENO, "2\n", 2);
	quick_sort_walls(vis_walls, 0, vis_walls_count - 1);
	write(STDOUT_FILENO, "3\n", 2);
	scale_walls(vis_walls, vis_walls_count);
	write(STDOUT_FILENO, "4\n", 2);
	draw_walls();
	write(STDOUT_FILENO, "5\n", 2);
}
