/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   squarify_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:07:43 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/04 09:51:43 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

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
	while (data()->input_data->map[i])
	{
		current_line_length = tiles_len(data()
				->input_data->map[i]);
		if (current_line_length > longest_line_length)
			longest_line_length = current_line_length;
		i++;
	}
	return (longest_line_length);
}

void	squarify_map(void)
{
	t_input_data	*data;
	t_tile_type		***tiles;
	int				new_len;
	int				i;
	int				j;

	data = data()->input_data;
	new_len = get_longest_line_length();
	tiles = gc_malloc((tiles_len3(data->map) + 1) * sizeof(t_tile_type **));
	i = 0;
	while (data->map && data->map[i])
	{
		j = -1;
		tiles[i] = gc_malloc((new_len + 1) * sizeof(t_tile_type *));
		while (data->map[i][++j])
		{
			tiles[i][j] = gc_malloc(sizeof(t_tile_type));
			*(tiles[i][j]) = *(data->map[i][j]);
		}
		while (j < new_len)
		{
			tiles[i][j] = gc_malloc(sizeof(t_tile_type));
			*(tiles[i][j++]) = VOID;
		}
		i++;
	}
	data()->input_data->map = tiles;
}
