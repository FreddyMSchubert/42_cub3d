/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:56:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 11:04:45 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	rad_to_deg(double radians)
{
	return (radians * (180.0 / M_PI));
}

t_vec2	deg_to_dir_vec(double degrees)
{
	t_vec2	dir;
	double	radians;

	radians = deg_to_rad(degrees);
	dir.x = cos(radians);
	dir.y = sin(radians);
	return (dir);
}

double	dir_vec_to_deg(t_vec2 dir)
{
	double	radians;
	double	degrees;

	radians = atan2(dir.y, dir.x);
	degrees = rad_to_deg(radians);
	return (normalize_degrees(degrees));
}

double	normalize_degrees(double degrees)
{
	degrees = fmod(degrees, 360.0);
	if (degrees < 0)
		degrees += 360.0;
	return degrees;
}

// if direction is 1, rotate clockwise, if -1, rotate counterclockwise
t_vec2	rotate_vector_by_90_degrees(t_vec2 v, int direction)
{
	t_vec2	rotated;

	rotated.x = v.y * direction;
	rotated.y = -v.x * direction;
	return (rotated);
}
