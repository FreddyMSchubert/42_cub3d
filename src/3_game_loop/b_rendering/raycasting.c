/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:22:19 by freddy            #+#    #+#             */
/*   Updated: 2024/06/19 14:02:43 by jkauker          ###   ########.fr       */
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
	return (t1);
}

t_vec2	raycast_intersect(t_transform t1, t_transform t2)
{
	double	denom;
	double	t;
	double	u;
	t_vec2	intersection;

	intersection.x = -1;
	intersection.y = -1;
	denom = t1.rot.x * t2.rot.y - t1.rot.y * t2.rot.x;
	if (denom == 0.0)
		return (intersection);
	t = ((t2.pos.x - t1.pos.x) * t2.rot.y - \
		(t2.pos.y - t1.pos.y) * t2.rot.x) / denom;
	u = ((t2.pos.x - t1.pos.x) * t1.rot.y - \
		(t2.pos.y - t1.pos.y) * t1.rot.x) / denom;
	if (t >= 0.0 && u >= 0.0 && u <= 1.0)
	{
		intersection.x = t1.pos.x + t * t1.rot.x;
		intersection.y = t1.pos.y + t * t1.rot.y;
	}
	return (intersection);
}

t_transform	*get_intersection_wall(t_transform **walls, t_transform ray)
{
	t_transform	*closest_wall;
	t_vec2		intersection;
	double		closest_distance;
	double		current_distance;
	int			i;

	closest_wall = NULL;
	closest_distance = -1;
	i = -1;
	while (walls[++i])
	{
		intersection = raycast_intersect(ray, *walls[i]);
		if (intersection.x != -1)
		{
			current_distance = pos_distance(ray.pos, intersection);
			if (closest_distance == -1 || current_distance < closest_distance)
			{
				closest_distance = current_distance;
				closest_wall = walls[i];
			}
		}
	}
	return (closest_wall);
}

double	get_ray_distance(t_transform **walls, t_transform ray, char *d, char *wall_orientation)
{
	t_vec2		intersection;
	t_transform	*closest_wall;
	double		closest_distance;
	double		current_distance;
	int			i;

	closest_distance = -1;
	i = -1;
	while (walls[++i])
	{
		intersection = raycast_intersect(ray, *walls[i]);
		if (intersection.x != -1)
		{
			current_distance = pos_distance(ray.pos, intersection);
			if (closest_distance == -1 || current_distance < closest_distance)
			{
				closest_distance = current_distance;
				closest_wall = walls[i];
			}
		}
	}
	*d = get_color_for_wall(*closest_wall);
	if (fabs(closest_wall->rot.x) > fabs(closest_wall->rot.y))
		*wall_orientation = 'H';
	else
		*wall_orientation = 'V';
	return (closest_distance);
}

/**
 * Calculate the deviation angle in degrees between a transform and a given pos.
 *
 * @param player e.g. the player's position and view direction (t_transform).
 * @param pos The target position to calculate the deviation for (t_vec2).
 * @return The deviation angle in degrees.
 * 
 * while loops are so we dont end up with -1000 degrees
 */
double	calculate_deviation_angle(t_transform p, t_vec2 pos)
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
	return (radians_to_degrees(deviation_angle));
}
