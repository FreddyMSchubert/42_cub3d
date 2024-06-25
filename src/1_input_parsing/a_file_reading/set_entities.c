/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:06:43 by freddy            #+#    #+#             */
/*   Updated: 2024/06/25 16:55:24 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_goal(t_vec2 pos, t_tile_type ***map)
{
	mlx_texture_t	*texture;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = mlx_load_png("./assets/entities/star.png");
	if (!texture)
		cub_exit("Failed to load goal texture!", -1);
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, GOAL_E, texture, true, tick_goal);
	return (true);
}

bool	set_key(t_vec2 pos, t_tile_type ***map)
{
	mlx_texture_t	*texture;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	texture = mlx_load_png("./assets/entities/key.png");
	if (!texture)
		cub_exit("Failed to load key texture!", -1);
	create_entity((t_transform){{pos.x + 0.5, pos.y + 0.5}, {1.0 , 0}}, KEY_E, texture, true, tick_key);
	return (true);
}

bool	set_door(t_vec2 pos, t_tile_type ***map, char type)
{
	mlx_texture_t	*texture;
	t_door			*data;
	t_entity		*ntt;
	t_transform		trans;

	*(map[(int)pos.y][(int)pos.x]) = FLOOR;
	data = gc_malloc(sizeof(t_door));
	if (type == 'H')
		data->direction = DOOR_DIR_HORIZONTAL;
	else
		data->direction = DOOR_DIR_VERTICAL;
	texture = mlx_load_png("./assets/entities/door.png");
	if (!texture)
		cub_exit("Failed to load door texture!", -1);
	trans.pos = (t_vec2){pos.x + 0.5, pos.y + 0.5};
	trans.rot = (t_vec2){0, 0};
	if (data->direction == DOOR_DIR_HORIZONTAL)
		trans.rot.x = 1;
	else
		trans.rot.y = 1;
	data->locked = true;
	ntt = create_entity(trans, DOOR_E, texture, false, tick_door);
	ntt->data = data;
	return (true);
}