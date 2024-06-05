/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squarify_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:07:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/05 18:51:47 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"
#include <stdio.h>

static int	tiles_len(t_tile_type **tiles)
{
	int	i;

	i = 0;
	while (tiles && tiles[i])
		i++;
	return (i);
}

static int	tiles_len3(t_tile_type ***tiles)
{
	int	i;

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

	j = -1; // when i set this to 0 so the loop starts at 1 it works but thats weird cuz it should start at the first and not the second
	tiles[i] = gc_malloc((new_len + 1) * sizeof(t_tile_type *));
	while (data->map[i][++j] && *(data->map[i][j]))
	{
		tiles[i][j] = gc_malloc(sizeof(t_entity_type));
		*(tiles[i][j]) = *(data->map[i][j]); // TODO: *(data->map[i][j]) is a segv when i > 0
	}
	while (j < new_len)
	{
		tiles[i][j] = gc_malloc(sizeof(t_entity_type));
		*(tiles[i][j++]) = VOID;
	}
}

void	squarify_map(void)
{
	t_input_data	*data;
	t_tile_type		***tiles;
	int				new_len;
	int				i;

	data = game()->input_data;
	new_len = get_longest_line_length();
	tiles = gc_malloc((tiles_len3(data->map) + 1) * sizeof(t_tile_type **));
	i = -1;
	while (data->map && data->map[++i])
		process_map_row(i, new_len, tiles, data);
	game()->input_data->map = tiles;
}
