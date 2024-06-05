/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:15:34 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/04 12:54:39 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	draw_wall(t_wall_scale *wall, mlx_image_t *img);

void	do_wall_operations(void)
{
	t_transform	vis_walls[RAYCASTS_PER_DEG * FOV_DEG];
	int			vis_walls_count;

	vis_walls_count = 0;
	get_visible_walls(vis_walls, &vis_walls_count);
	quick_sort_walls(vis_walls, 0, vis_walls_count - 1);
	scale_walls(vis_walls, vis_walls_count);
	draw_walls();
    t_wall_scale test = (t_wall_scale){10, 100, 50, 300, 'E'};
    draw_wall(&test, game()->game_scene);
}
