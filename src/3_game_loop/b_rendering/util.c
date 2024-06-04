/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:22:19 by freddy            #+#    #+#             */
/*   Updated: 2024/05/29 08:45:21 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

double	pos_distance(t_vec2 pos1, t_vec2 pos2)
{
	return (sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)));
}

// makes the rot of a vector be as long as the defined distance
// e.g. for view distances
t_vec2	scale_transform(t_vec2 t1, double distance)
{
	double	current_magnitude;
	double	scale_factor;

	current_magnitude = sqrt(t1.x * t1.x + t1.y * t1.y);
	if (current_magnitude != 0)
	{
		scale_factor = distance / current_magnitude;
		t1.x *= scale_factor;
		t1.y *= scale_factor;
	}
	return t1;
}

t_vec2	*raycast_intersect(t_transform t1, t_transform t2)
{
	double	denom;
	double	t;
	double	u;
	t_vec2	*intersection;

	denom = t1.rot.x * t2.rot.y - t1.rot.y * t2.rot.x;
	if (denom == 0.0)
		return (NULL);
	t = ((t2.pos.x - t1.pos.x) * t2.rot.y - \
		(t2.pos.y - t1.pos.y) * t2.rot.x) / denom;
	u = ((t2.pos.x - t1.pos.x) * t1.rot.y - \
		(t2.pos.y - t1.pos.y) * t1.rot.x) / denom;
	if (t >= 0.0 && u >= 0.0 && u <= 1.0)
	{
		intersection = (t_vec2 *)malloc(sizeof(t_vec2));
		intersection->x = t1.pos.x + t * t1.rot.x;
		intersection->y = t1.pos.y + t * t1.rot.y;
		return (intersection);
	}
	return (NULL);
}
