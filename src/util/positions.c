/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:05:18 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/13 09:21:31 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	is_same_wall(t_transform wall1, t_transform wall2)
{
	if (wall1.pos.x != wall2.pos.x)
		return (false);
	if (wall1.pos.y != wall2.pos.y)
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

char	get_color_for_wall(t_vec2 pos)
{
	if ((int)pos.x % 1 == 0)
	{
		// vertical wall
		if (player()->transform.pos.y < pos.y)
			return ('N');
		else
			return ('S');
	}
	else
	{
		// horizontal wall
		if (player()->transform.pos.x < pos.x)
			return ('E');
		else
			return ('W');
	}
}
