/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/02 10:43:16 by fschuber         ###   ########.fr       */
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
	if (!amount)
	{
		mlx_put_string(game()->mlx, "?", x, y);
		return ;
	}
	amount_text = get_amount_text_by_index(index);
	if (!*amount_text)
		*amount_text = mlx_put_string(game()->mlx, amount, x + 4, y);
	free(amount);
}

static inline void	draw_current_selection(int start_x, int start_y,
	int size, int border_size)
{
	int			i;
	t_inventory	inv;

	inv = player()->inv;
	i = -1;
	(void)border_size;
	while (++i < inv.num_available_items)
	{
		if (i == inv.current_index)
			draw_rectangle((t_scale){i * size + start_x, start_y},
				(t_scale){size, size}, (t_color){0, 255, 0, 255});
		else
			draw_rectangle((t_scale){i * size + start_x, start_y},
				(t_scale){size, size}, (t_color){0, 0, 255, 255});
		draw_item_at(i, i * size + start_x, start_y, size);
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
		player()->inv.current_index %= player()->inv.num_available_items;
	}
}

static inline void	draw_hand_item(int pos_x, int pos_y, int size_x, int size_y)
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
	int	size;

	i = -1;
	size = game()->mlx->width / 15;
	start_x = game()->mlx->width / 2 - (size * 5) / 2;
	start_y = game()->mlx->height - size;
	draw_hand_item(game()->mlx->width - size * 2.3, \
					game()->mlx->height - size * 2.3,
		size * 2, size * 2);
	while (++i < player()->inv.num_available_items)
		draw_current_selection(start_x, start_y, size, 10);
	draw_healthbar(size / 2, start_x, start_y);
}
