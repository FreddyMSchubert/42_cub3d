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

#include "../../../../../include/cub3d.h"

bool	is_visible(int x, int y);

int	get_opacity(int x, int y, int id)
{
	double	distance;
	int		min_opacity;
	int		max_opacity;
	bool	visible;

	min_opacity = 75;
	max_opacity = 255;
	distance = sqrt(pow(player(id)->transform.pos.x - x, 2)
			+ pow(player(id)->transform.pos.y - y, 2));
	visible = is_visible(x, y);
	if (!visible && distance >= 3)
		return (0);
	if (max_opacity * (distance / 100) > max_opacity)
		return (max_opacity);
	if (max_opacity - (max_opacity * (distance / 10)) < min_opacity)
		return (min_opacity);
	return (max_opacity - (max_opacity * (distance / 10)));
}

void	draw_tile(t_scale ij, int size, int offset_x, int offset_y, int id)
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
	if (*(walls[i][j]) == VOID)
		draw_square_hud(draw_x, draw_y, size,
			rgba_to_int(50, 50, 50, get_opacity(j, i, id)), id);
	else if (*(walls[i][j]) == WALL)
		draw_square_hud(draw_x, draw_y, size,
			rgba_to_int(255, 0, 0, get_opacity(j, i, id)), id);
	else if (*(walls[i][j]) == FLOOR)
		draw_square_hud(draw_x, draw_y, size,
			rgba_to_int(0, 255, 0, get_opacity(j, i, id)), id);
}

static inline void	draw_walls(int size, int id)
{
	int			i;
	int			j;
	int			offset_x;
	int			offset_y;
	t_tile_type	***walls;

	i = -1;
	offset_x = MINIMAP_WIDTH / 2 - (player(id)->transform.pos.x * size);
	offset_y = MINIMAP_HEIGHT / 2 - (player(id)->transform.pos.y * size);
	walls = game()->input_data->map;
	while (walls[++i])
	{
		j = -1;
		while (walls[i][++j])
			draw_tile((t_scale){i, j}, size, offset_x, offset_y, id);
	}
}

static inline void	draw_player(int size, int id)
{
	draw_square_hud(player(id)->hud->width / 2 - size / 2,
		player(id)->hud->height / 2 - size / 2, size / 2,
		rgba_to_int(0, 0, 255, 255), id);
}

void	hud_draw_minimap(int id)
{
	int	size;

	size = 6;
	draw_walls(size, id);
	draw_player(size, id);
}
