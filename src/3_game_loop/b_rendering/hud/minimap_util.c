/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:43:49 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/02 10:45:21 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

int	get_floor_color(int j, int i)
{
	t_color	color;

	color = game()->input_data->floor_color;
	color = with_opacity(color, get_minimap_opacity(j, i));
	return (t_color_to_int(color));
}

int	get_wall_color(int j, int i)
{
	t_color	floor_color;

	floor_color = game()->input_data->floor_color;
	if (floor_color.r + floor_color.g + floor_color.b < 200)
		return (rgba_to_int(255, 255, 255, get_minimap_opacity(j, i)));
	return (rgba_to_int(0, 0, 0, get_minimap_opacity(j, i)));
}
