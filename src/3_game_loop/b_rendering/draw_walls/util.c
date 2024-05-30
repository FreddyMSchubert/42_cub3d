/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:53:10 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 12:29:38 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

/**
 * Calculate the deviation angle in degrees between a transform and a given position.
 *
 * @param player e.g. the player's position and view direction (t_transform).
 * @param pos The target position to calculate the deviation for (t_vec2).
 * @return The deviation angle in degrees.
 * 
 * while loops are so we dont end up with -1000 degrees
 */
double calculate_deviation_angle(t_transform p, t_vec2 pos)
{
	double	pos_angle;
	double	player_angle;
	double	deviation_angle;

	pos_angle = atan2(pos.y - p.pos.y, pos.x - p.pos.x);
	player_angle = atan2(p.rot.y, p.rot.x);
	deviation_angle = pos_angle - player_angle;
	while (deviation_angle > M_PI)
		deviation_angle -= 2 * M_PI;
	while (deviation_angle < -M_PI)
		deviation_angle += 2 * M_PI;
	return radians_to_degrees(deviation_angle);
}
