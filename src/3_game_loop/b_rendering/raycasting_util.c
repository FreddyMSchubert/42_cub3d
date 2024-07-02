/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:08:51 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/02 11:09:07 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

double	pos_dist(t_vec2 pos1, t_vec2 pos2)
{
	double	dx;
	double	dy;

	dx = pos2.x - pos1.x;
	dy = pos2.y - pos1.y;
	return (sqrt(dx * dx + dy * dy));
}

t_vec2	scale_vector(t_vec2 v, double distance)
{
	double	current_magnitude;
	double	scale_factor;

	current_magnitude = sqrt(v.x * v.x + v.y * v.y);
	if (current_magnitude == 0)
		return (v);
	scale_factor = distance / current_magnitude;
	v.x *= scale_factor;
	v.y *= scale_factor;
	return (v);
}

t_vec2	raycast_intersect(t_transform t1, t_transform t2)
{
	double	denom;
	double	inv_denom;
	double	t;
	double	u;
	t_vec2	intersection;

	intersection.x = -1;
	intersection.y = -1;
	denom = t1.rot.x * t2.rot.y - t1.rot.y * t2.rot.x;
	inv_denom = 1.0 / denom;
	t = ((t2.pos.x - t1.pos.x) * t2.rot.y - \
		(t2.pos.y - t1.pos.y) * t2.rot.x) * inv_denom;
	u = ((t2.pos.x - t1.pos.x) * t1.rot.y - \
		(t2.pos.y - t1.pos.y) * t1.rot.x) * inv_denom;
	if (t >= 0.0 && u >= 0.0 && u <= 1.0)
	{
		intersection.x = t1.pos.x + t * t1.rot.x;
		intersection.y = t1.pos.y + t * t1.rot.y;
	}
	return (intersection);
}
