/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:45:16 by freddy            #+#    #+#             */
/*   Updated: 2024/06/04 09:52:13 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

// if positive, turn right
void	turn(double degrees)
{
	t_vec2	direction;
	double	cos_angle;
	double	sin_angle;
	t_vec2	new_direction;

	direction = player()->transform.rot;
	cos_angle = cos(degrees * M_PI / 180.0);
	sin_angle = sin(degrees * M_PI / 180.0);
	new_direction.x = direction.x * cos_angle - direction.y * sin_angle;
	new_direction.y = direction.x * sin_angle + direction.y * cos_angle;
	player()->transform.rot = new_direction;
}
