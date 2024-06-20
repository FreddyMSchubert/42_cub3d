/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 03:32:53 by freddy            #+#    #+#             */
/*   Updated: 2024/06/20 05:14:26 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

t_transform	get_wall_from_intersect(t_vec2 intersect)
{
	t_transform	wall;

	wall.rot.x = 0;
	wall.rot.y = 0;
	wall.pos.x = intersect.x;
	wall.pos.y = intersect.y;
	if (has_decimals(intersect.x))
	{
		wall.rot.x = 1;
		wall.pos.x = floor(intersect.x);
	}
	else
	{
		wall.rot.y = 1;
		wall.pos.y = floor(intersect.y);
	}
	return (wall);
}

bool	get_wall_orientation(t_vec2 intersect)
{
	if (get_wall_from_intersect(intersect).rot.x == 0)
		return (WALL_ORIENTATION_VERTICAL);
	return (WALL_ORIENTATION_HORIZONTAL);
}


char	get_wall_face_to_render(t_vec2 intersect)
{
	t_transform wall;

	wall = get_wall_from_intersect(intersect);
	if (wall.rot.x == 0.0)
	{
		if (player()->transform.pos.x < wall.pos.x)
			return (WALL_FACE_EAST);
		else
			return (WALL_FACE_WEST);
	}
	else
	{
		if (player()->transform.pos.y < wall.pos.y)
			return (WALL_FACE_SOUTH);
		else
			return (WALL_FACE_NORTH);
	}
}
