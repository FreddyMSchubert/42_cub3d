/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 13:58:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

void	sort_and_raycast_walls(void)
{
	get_persistent_data()->raycasted_sorted_walls = get_persistent_data()->input_data->walls;
}
