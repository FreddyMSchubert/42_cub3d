/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/06 12:59:19 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int				*get_amount_of_item(int index);
mlx_texture_t	*get_tex_by_index(int index);
mlx_image_t		**get_amount_text_by_index(int index);
void			draw_rectangle(t_scale pos, t_scale size, t_color color);

static void	draw_item_at(unsigned int index, int x, int y, int size)
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
	texture_draw(tex, (t_scale){x + 1, y + 1},
		(t_scale){size - 2, size - 2});
	amount = ft_itoa(*get_amount_of_item(index));
	amount_text = get_amount_text_by_index(index);
	if (!amount && !*amount_text)
		*amount_text = mlx_put_string(game()->mlx, "?", x, y);
	else if (!*amount_text)
		*amount_text = mlx_put_string(game()->mlx, amount, x + 4, y);
	free(amount);
}

static inline void	draw_current_selection(int start_x, int start_y,
	int size)
{
	int			i;
	t_inventory	inv;

	inv = player()->inv;
	i = -1;
	while (++i < inv.num_available_items)
		draw_item_at(i, i * size + start_x + 10, start_y + 10, size - 20);
}

void	snap_to_item(int dir, int i)
{
	player()->inv.current_index %= player()->inv.num_available_items;
	if (dir < 0)
	{
		while ((*get_amount_of_item(player()->inv.current_index)) == 0 && ++i
			< player()->inv.num_available_items)
		{
			player()->inv.current_index--;
			if (player()->inv.current_index < 0)
				player()->inv.current_index = player()->inv.num_available_items
				- 1;
		}
	}
	else
	{
		while ((*get_amount_of_item(player()->inv.current_index)) == 0 && ++i
			< player()->inv.num_available_items)
		{
			player()->inv.current_index++;
			if (player()->inv.current_index
				>= player()->inv.num_available_items)
				player()->inv.current_index = 0;
		}
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
				>= player()->inv.num_available_items)
				player()->inv.current_index = 0;
		}
		else
		{
			player()->inv.current_index += direction;
			if (player()->inv.current_index < 0)
				player()->inv.current_index = player()->inv.num_available_items
				- 1;
		}
		snap_to_item(direction, 0);
	}
}

void	draw_inventory(void)
{
	int	i;
	int	start_x;
	int	start_y;
	int	size;

	i = -1;
	size = game()->mlx->width / 15;
	start_x = game()->mlx->width / 2 - (size * 5) / 2;
	start_y = game()->mlx->height - size - 2;
	texture_draw(game()->textures.hotbar, (t_scale){start_x, start_y},
		(t_scale){size * 5, size});
	texture_draw(game()->textures.hotbar_select,
		(t_scale){start_x + size * player()->inv.current_index, start_y},
		(t_scale){size, size});
	while (++i < player()->inv.num_available_items)
		draw_current_selection(start_x, start_y, size);
	draw_healthbar(size / 2, start_x, start_y);
	if (game()->boss)
		draw_boss_healthbar(size / (1.0 + ((game()->boss->health - 3.0) / \
							(50.0 - 3.0)) * (3.3 - 1.0)));
}
