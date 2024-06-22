/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 03:32:53 by freddy            #+#    #+#             */
/*   Updated: 2024/06/22 18:26:19 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

/*
	Checked for larger diff between decimals instead of just intersect.x != 0.0
	To account for floating point imprecisions
*/
t_transform	get_wall_from_intersect(t_vec2 intersect)
{
	t_transform	wall;
	float		decimalsX;
	float		decimalsY;

	wall.rot = (t_vec2){0, 0};
	wall.pos = intersect;
	decimalsX = fabs(intersect.x - floorf(intersect.x));
	decimalsY = fabs(intersect.y - floorf(intersect.y));
	if (decimalsX > decimalsY)
	{
		wall.rot.x = 1;
		wall.pos.x = floorf(intersect.x);
	}
	else
	{
		wall.rot.y = 1;
		wall.pos.y = floorf(intersect.y);
	}
	return (wall);
}

bool	get_wall_orientation(t_vec2 intersect)
{
	if (get_wall_from_intersect(intersect).rot.x == 0)
		return (WALL_ORIENTATION_VERTICAL);
	return (WALL_ORIENTATION_HORIZONTAL);
}

// south west east inermixed
char	get_wall_face_to_render(t_vec2 intersect)
{
	t_transform	wall;

	wall = get_wall_from_intersect(intersect);
	if (wall.rot.x == 0.0)
	{
		if (player()->transform.pos.x <= wall.pos.x)
			return (WALL_FACE_EAST);
		else
			return (WALL_FACE_WEST);
	}
	else
	{
		if (player()->transform.pos.y <= wall.pos.y)
			return (WALL_FACE_SOUTH);
		else
			return (WALL_FACE_NORTH);
	}
}
