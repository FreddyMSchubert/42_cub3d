/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/26 15:28:37 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static inline void	draw_rectangle(t_scale pos, t_scale size, t_color color)
{
	int	x;
	int	y;

	x = pos.x;
	while (x < pos.x + size.x)
	{
		y = pos.y;
		while (y < pos.y + size.y)
		{
			if (x == pos.x || x == pos.x + size.x - 1
				|| y == pos.y || y == pos.y + size.y - 1)
				mlx_put_pixel(game()->game_scene, x, y,
					rgba_to_int(color.r, color.g, color.b, color.a));
			y++;
		}
		x++;
	}
}

static inline void	draw_current_selection(int selection)
{
	int			i;
	t_inventory	inv;

	inv = player()->inv;
	i = -1;
	while (++i < inv.num_available_items)
	{
		if (i == selection)
			draw_rectangle((t_scale){i * 50, 0}, (t_scale){50, 50},
				(t_color){0, 255, 0, 255});
		else
			draw_rectangle((t_scale){i * 50, 0}, (t_scale){50, 50},
				(t_color){0, 0, 255, 255});
	}
}

void	cycle_inventory(int direction, bool direct)
{
	if (direction == 0 && !direct)
		return ;
	if (!direct)
	{
		direction = direction % player()->inv.num_available_items;
		player()->inv.current_index = direction;
	}
	else
	{
		if (direction > 0)
		{
			player()->inv.current_index += direction;
			if (player()->inv.current_index
				>= player()->inv.num_available_items)
				player()->inv.current_index = 0;
		}
		else
		{
			player()->inv.current_index -= direction;
			if (player()->inv.current_index < 0)
				player()->inv.current_index = player()->inv.num_available_items
				- 1;
		}
	}
	printf("Current index: %d\n", player()->inv.current_index);
}

void	draw_inventory(void)
{
	int	i;

	i = -1;
	while (++i < player()->inv.num_available_items)
		draw_current_selection(i);
}
