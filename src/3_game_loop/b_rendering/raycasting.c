/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:22:19 by freddy            #+#    #+#             */
/*   Updated: 2024/07/01 12:13:30 by freddy           ###   ########.fr       */
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
	if (fabs(denom) < DBL_EPSILON)
		return (intersection);
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

t_vec2	get_wall_intersection(t_transform **walls, t_transform ray)
{
	t_vec2		intersection;
	t_vec2		closest_intersection;
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
			current_distance = pos_dist(ray.pos, intersection);
			if (closest_distance == -1 || current_distance < closest_distance)
			{
				closest_distance = current_distance;
				closest_intersection = intersection;
			}
		}
	}
	return (closest_intersection);
}

t_vec2	*get_entity_intersection(t_transform ray, t_entity ***entities)
{
	int			size;
	t_vec2		*intersections;
	t_entity	*entity;
	t_vec2		intersection;
	t_list		*current;

	size = ft_lstsize(game()->entities);
	intersections = malloc((size + 1) * sizeof(t_vec2));
	*entities = malloc((size + 1) * sizeof(t_entity *));
	if (!entities)
		cub_exit("Memory allocation failed", -1);
	current = game()->entities;
	size = 0;
	while (current)
	{
		entity = (t_entity *)current->content;
		intersection = raycast_intersect(ray, get_face_vector(entity));
		if (intersection.x != -1)
		{
			(*entities)[size] = entity;
			intersections[size] = intersection;
			size++;
		}
		current = current->next;
	}
	intersections[size].x = -1;
	intersections[size].y = -1;
	(*entities)[size] = NULL;
	return (intersections);
}
