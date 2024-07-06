/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 03:32:53 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:16:09 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

/*
	Checked for larger diff between decimals instead of just intersect.x != 0.0
	To account for floating point imprecisions
*/
t_trans	get_wall_from_intersect(t_vec2 intersect)
{
	t_trans		wall;
	float		decimals_x;
	float		decimals_y;

	wall.rot = (t_vec2){0, 0};
	wall.pos = intersect;
	decimals_x = fabs(intersect.x - floorf(intersect.x));
	decimals_y = fabs(intersect.y - floorf(intersect.y));
	if (decimals_x > decimals_y)
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

char	get_wall_face_to_render(t_vec2 intersect)
{
	t_trans	wall;

	wall = get_wall_from_intersect(intersect);
	if (wall.rot.x == 0.0)
	{
		if (player()->trans.pos.x <= wall.pos.x)
			return (WALL_FACE_EAST);
		else
			return (WALL_FACE_WEST);
	}
	else
	{
		if (player()->trans.pos.y <= wall.pos.y)
			return (WALL_FACE_SOUTH);
		else
			return (WALL_FACE_NORTH);
	}
}

double	get_fisheye_corrected_ray_angle(int ray_index)
{
	double	relative_position;
	double	angle_correction;

	relative_position = ((double)ray_index / \
						((RAYCASTS_PER_DEG * FOV_DEG) / 2)) - 1;
	angle_correction = atan(relative_position * tan(deg_to_rad(FOV_DEG / 2)));
	return (rad_to_deg(angle_correction));
}

mlx_texture_t	*get_wall_texture(char d)
{
	if (d == 'N')
		return (game()->no_texture);
	if (d == 'E')
		return (game()->ea_texture);
	if (d == 'S')
		return (game()->so_texture);
	if (d == 'W')
		return (game()->we_texture);
	return (NULL);
}
