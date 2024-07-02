/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:22:19 by freddy            #+#    #+#             */
/*   Updated: 2024/07/02 11:14:25 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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

static inline void	setup_entities(t_vec2 **intersections, t_entity ***entities)
{
	int	size;

	size = ft_lstsize(game()->entities);
	*intersections = malloc(sizeof(t_vec2) * (size + 1));
	*entities = malloc(sizeof(t_entity *) * (size + 1));
	if (!entities)
		cub_exit("Memory allocation failed", -1);
}

t_vec2	*get_entity_intersection(t_transform ray, t_entity ***entities)
{
	int			size;
	t_vec2		*intersections;
	t_entity	*entity;
	t_vec2		intersection;
	t_list		*current;

	setup_entities(&intersections, entities);
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
