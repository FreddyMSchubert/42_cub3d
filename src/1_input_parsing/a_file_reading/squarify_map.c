/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squarify_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:07:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/27 22:22:57 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	tiles_len(t_tile_type **tiles)
{
	int	i;

	if (!tiles)
		return (0);
	i = 0;
	while (tiles && tiles[i])
		i++;
	return (i);
}

static int	tiles_len3(t_tile_type ***tiles)
{
	int	i;

	if (!tiles)
		return (0);
	i = 0;
	while (tiles && tiles[i])
		i++;
	return (i);
}

static int	get_longest_line_length(void)
{
	int		i;
	int		longest_line_length;
	int		current_line_length;

	if (!game()->input_data->map)
		return (0);
	i = 0;
	longest_line_length = 0;
	while (game()->input_data->map[i])
	{
		current_line_length = tiles_len(game()
				->input_data->map[i]);
		if (current_line_length > longest_line_length)
			longest_line_length = current_line_length;
		i++;
	}
	return (longest_line_length);
}

static void	process_map_row(int i, int new_len, t_tile_type ***tiles,
	t_input_data *data)
{
	int	j;

	j = 0;
	tiles[i] = gc_malloc((new_len + 1) * sizeof(t_tile_type *));
	while (data->map[i][j])
	{
		tiles[i][j] = gc_malloc(sizeof(t_tile_type));
		*(tiles[i][j]) = *(data->map[i][j]);
		j++;
	}
	while (j < new_len)
	{
		tiles[i][j] = gc_malloc(sizeof(t_tile_type));
		*(tiles[i][j]) = VOID;
		j++;
	}
}

void	squarify_map(void)
{
	t_input_data	*data;
	t_tile_type		***tiles;
	int				new_len;
	int				i;

	data = game()->input_data;
	if (!data || !data->map)
		return ;
	new_len = get_longest_line_length();
	tiles = gc_malloc((tiles_len3(data->map) + 1) * sizeof(t_tile_type **));
	i = -1;
	while (data->map && data->map[++i])
		process_map_row(i, new_len, tiles, data);
	game()->input_data->map_height = i;
	game()->input_data->map_width = new_len;
	game()->input_data->map = tiles;
}
