/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:18 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/13 10:34:22 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_same_wall(t_transform wall1, t_transform wall2)
{
	if (wall1.rot.x != wall2.rot.x)
		return (false);
	if (wall1.rot.y != wall2.rot.y)
		return (false);
	if (wall1.rot.x != wall2.rot.x)
		return (false);
	if (wall1.rot.y != wall2.rot.y)
		return (false);
	return (true);
}

t_vec2	sum_vectors(t_vec2 v1, t_vec2 v2)
{
	t_vec2	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	return (result);
}

char	get_color_for_wall(t_transform t)
{
	printf("transform: %d %d - %d %d\n", (int)t.pos.x, (int)t.pos.y, (int)t.rot.x, (int)t.rot.y);
	if (t.rot.x == 0.0)
	{
		// vertical wall
		if (player()->transform.pos.x < t.pos.x)
			return ('N');
		else
			return ('S');
	}
	else
	{
		// horizontal wall
		if (player()->transform.pos.y < t.pos.y)
			return ('E');
		else
			return ('W');
	}
}
