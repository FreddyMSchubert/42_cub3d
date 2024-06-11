/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:15:34 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/11 14:33:35 by freddy           ###   ########.fr       */
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
		vis_walls[i] = *game()->input_data->walls[i];
	quick_sort_walls(vis_walls, 0, vis_walls_count - 1);
	scale_walls(vis_walls, vis_walls_count);
}
