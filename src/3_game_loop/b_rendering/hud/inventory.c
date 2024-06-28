/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/28 13:19:05 by freddy           ###   ########.fr       */
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

int	*get_amount_of_item(int index)
{
	if (index == 0)
		return (&(player()->inv.keys));
	else if (index == TYPE_WATER + 1)
		return (&(player()->inv.water_orbs));
	else if (index == TYPE_FIRE + 1)
		return (&(player()->inv.fire_orbs));
	else if (index == TYPE_EARTH + 1)
		return (&(player()->inv.earth_orbs));
	else if (index == TYPE_AIR + 1)
		return (&(player()->inv.air_orbs));
	return (0);
}

mlx_texture_t	*get_tex_by_index(int index)
{
	mlx_texture_t	*tex;

	if (!*get_amount_of_item(index) || index < 0 || index > player()->inv.num_available_items)
		return (NULL);
	if (index == 0)
		tex = mlx_load_png("./assets/textures/entities/key.png");
	else if (index == TYPE_WATER + 1)
		tex = mlx_load_png("./assets/textures/entities/orbs/water.png");
	else if (index == TYPE_FIRE + 1)
		tex = mlx_load_png("./assets/textures/entities/orbs/fire.png");
	else if (index == TYPE_EARTH + 1)
		tex = mlx_load_png("./assets/textures/entities/orbs/earth.png");
	else if (index == TYPE_AIR + 1)
		tex = mlx_load_png("./assets/textures/entities/orbs/air.png");
	else
	 	tex = NULL;
	return (tex);
}

mlx_image_t	**get_amount_text_by_index(int index)
{
	if (index == 0)
		return (&(player()->inv.text_amount_key));
	else if (index == TYPE_WATER + 1)
		return (&(player()->inv.text_amount_water));
	else if (index == TYPE_FIRE + 1)
		return (&(player()->inv.text_amount_fire));
	else if (index == TYPE_EARTH + 1)
		return (&(player()->inv.text_amount_earth));
	else
		return (&(player()->inv.text_amount_air));
}

static void draw_item_at(unsigned int index, int x, int y)
{
	mlx_texture_t	*tex;
	t_inventory		inv;
	char			*amount;
	mlx_image_t		**amount_text;

	inv = player()->inv;
	tex = NULL;
	amount = NULL;
	if (index >= (unsigned int)inv.num_available_items)
		return ;
	tex = get_tex_by_index(index);
	if (!tex)
		return ;
	texture_draw(tex, (t_scale){x + 1, y + 1}, (t_scale){49, 46});
	amount = ft_itoa(*get_amount_of_item(index));
	if (!amount)
	{
		mlx_put_string(game()->mlx, "?", x, y);
		return ;
	}
	amount_text = get_amount_text_by_index(index);
	if (!*amount_text)
		*amount_text = mlx_put_string(game()->mlx, amount, x, y);
	free(amount);
}

static inline void	draw_current_selection(int start_x, int start_y)
{
	int			i;
	t_inventory	inv;

	inv = player()->inv;
	i = -1;
	while (++i < inv.num_available_items)
	{
		if (i == inv.current_index)
			draw_rectangle((t_scale){i * 50 + start_x, start_y}, (t_scale){50, 50},
				(t_color){0, 255, 0, 255});
		else
			draw_rectangle((t_scale){i * 50 + start_x, start_y}, (t_scale){50, 50},
				(t_color){0, 0, 255, 255});
		draw_item_at(i, i * 50 + start_x, start_y);
	}
}

void	cycle_inventory(int direction, bool direct)
{
	if (direction == 0 && !direct)
		return ;
	if (direct)
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
				> player()->inv.num_available_items)
				player()->inv.current_index = 0;
		}
		else
		{
			player()->inv.current_index += direction;
			if (player()->inv.current_index < 0)
				player()->inv.current_index = player()->inv.num_available_items
				- 1;
		}
	}
}

void	draw_hand_item(int pos_x, int pos_y, int size_x, int size_y)
{
	int				index;
	mlx_texture_t	*tex;

	index = player()->inv.current_index;
	tex = get_tex_by_index(index);
	if (index == -1 || !tex)
		return ;
	texture_draw(tex,
		(t_scale){pos_x, pos_y}, (t_scale){size_x, size_y});
}

void	draw_inventory(void)
{
	int	i;
	int	start_x;
	int	start_y;

	i = -1;
	start_x = game()->mlx->width / 2 - 150;
	start_y = game()->mlx->height - 50;
	draw_hand_item(start_y + 100, start_y - 150, 200, 200);
	while (++i < player()->inv.num_available_items)
		draw_current_selection(start_x, start_y);
}
