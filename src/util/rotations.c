/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:56:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/04 09:42:32 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / M_PI));
}

t_vec2	degrees_to_dir_vector(double degrees)
{
	t_vec2	dir;
	double	radians;

	radians = degrees_to_radians(degrees);
	dir.x = cos(radians);
	dir.y = sin(radians);
	return (dir);
}

double	dir_vector_to_degrees(t_vec2 dir)
{
	double	radians;
	double	degrees;

	radians = atan2(dir.y, dir.x);
	degrees = radians_to_degrees(radians);
	return (normalize_degrees(degrees));
}

double	normalize_degrees(double degrees)
{
	while (degrees < 0)
		degrees += 360;
	while (degrees >= 360)
		degrees -= 360;
	return (degrees);
}
