/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:15:34 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/11 12:29:29 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// scale walls calls draw walls
void	do_wall_operations(void)
{
	int			vis_walls_count;

	vis_walls_count = 0;
	while (game()->input_data->walls[vis_walls_count])
		vis_walls_count++;
	t_transform	vis_walls[vis_walls_count];
	int i = -1;
	while (++i < vis_walls_count)
	{
		vis_walls[i] = *game()->input_data->walls[i];
	}
	get_visible_walls(vis_walls, &vis_walls_count);
	quick_sort_walls(vis_walls, 0, vis_walls_count - 1);
	scale_walls(vis_walls, vis_walls_count);
}
