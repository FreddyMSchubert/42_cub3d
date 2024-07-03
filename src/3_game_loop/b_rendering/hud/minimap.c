/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:56:58 by jkauker            #+#    #+#            */
/*   Updated: 2024/06/24 10:13:05 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

bool	is_visible(int x, int y);

int	get_minimap_opacity(int x, int y)
{
	double	distance;
	int		min_opacity;
	int		max_opacity;
	bool	visible;

	min_opacity = 75;
	max_opacity = 255;
	distance = sqrt(pow(player()->transform.pos.x - x, 2)
			+ pow(player()->transform.pos.y - y, 2));
	visible = is_visible(x, y);
	if (!visible && distance >= 3)
		return (0);
	if (max_opacity * (distance / 100) > max_opacity)
		return (max_opacity);
	if (max_opacity - (max_opacity * (distance / 10)) < min_opacity)
		return (min_opacity);
	return (max_opacity - (max_opacity * (distance / 10)));
}

void	draw_tile(t_scale ij, int size, int offset_x, int offset_y)
{
	t_tile_type	***walls;
	int			draw_x;
	int			draw_y;
	int			j;
	int			i;

	i = ij.x;
	j = ij.y;
	walls = game()->input_data->map;
	draw_x = j * size + offset_x - size / 2;
	draw_y = i * size + offset_y - size / 2;
	if (*(walls[i][j]) == WALL || *(walls[i][j]) == VOID)
		draw_square_hud(draw_x, draw_y, size, get_wall_color(j, i));
	else if (*(walls[i][j]) == FLOOR)
		draw_square_hud(draw_x, draw_y, size, get_floor_color(j, i));
}

static inline void	draw_walls(int size)
{
	int			i;
	int			j;
	int			offset_x;
	int			offset_y;
	t_tile_type	***walls;

	i = -1;
	offset_x = MINIMAP_WIDTH / 2 - (player()->transform.pos.x * size);
	offset_y = MINIMAP_HEIGHT / 2 - (player()->transform.pos.y * size);
	walls = game()->input_data->map;
	while (walls[++i])
	{
		j = -1;
		while (walls[i][++j])
			draw_tile((t_scale){i, j}, size, offset_x, offset_y);
	}
}

void	hud_draw_minimap(void)
{
	int	size;

	size = 6;
	draw_walls(size);
	draw_square_hud(MINIMAP_WIDTH / 2 - size / 2,
		MINIMAP_HEIGHT / 2 - size / 2, size / 2,
		get_wall_color(player()->transform.pos.y, player()->transform.pos.x));
}
