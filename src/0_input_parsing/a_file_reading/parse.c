/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/28 08:21:58 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	regex(char *line, char *reg);
bool	char_is_in(char c, char *seq);
int		split_len(char **split);
bool	free_split(char	**split, bool ret);
void	set_player_spawn(char dir, t_vec2 pos);
bool	set_color(t_color *color, char *color_val);
bool	set_value(char	**value, char	*set);

bool	parse_attributes(char	**data, t_input_data **input_data, int *i)
{
	char	**split;

	if (!data[(*i)--])
		return (true);
	while (data[++(*i)])
	{
		if (data[*i][0] == 0)
			continue ;
		split = ft_split(data[*i], ' ');
		if (!split || split_len(split) != 2)
			return (free_split(split, true));
		if (str_is_equal(split[0], "NO")
			&& !set_value(&(*input_data)->no_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "SO")
			&& !set_value(&(*input_data)->so_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "WE")
			&& !set_value(&(*input_data)->we_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "EA")
			&& !set_value(&(*input_data)->ea_texture_location, split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "F")
			&& !set_color(&((*input_data)->floor_color), split[1]))
			return (free_split(split, false));
		else if (str_is_equal(split[0], "C")
			&& !set_color(&((*input_data)->ceiling_color), split[1]))
			return (free_split(split, false));
		else if (regex(data[*i], MAP_TILES))
			return (free_split(split, true));
		free_split(split, NULL);
	}
	return (true);
}

bool	parse_map(char **data, t_input_data **input_data, int *i)
{
	int			map_len;
	int			k;
	int			j;
	t_tile_type	***map;

	map_len = 0;
	while (data[(*i) + map_len] && regex(data[(*i) + map_len], MAP_TILES))
		map_len++;
	if (map_len < 3)
		return (false);
	map = gc_malloc((map_len + 1) * sizeof(t_tile_type **));
	map[map_len] = NULL;
	k = -1;
	while (data[*i] && regex(data[*i], MAP_TILES) && map_len--)
	{
		map[++k] = gc_malloc(ft_strlen(data[*i]) * sizeof(t_tile_type *) + 1);
		map[k][ft_strlen(data[*i])] = NULL;
		j = -1;
		while (data[*i][++j])
		{
			map[k][j] = gc_malloc(sizeof(t_tile_type));
			if (data[*i][j] == '0')
				*map[k][j] = FLOOR;
			else if (data[*i][j] == '1')
				*map[k][j] = WALL;
			else if (data[*i][j] == ' ')
				*map[k][j] = VOID;
			else
			{
				set_player_spawn(data[*i][j], (t_vec2){k, j});
				*map[k][j] = FLOOR;
			}
		}
		(*i)++;
	}
	(*input_data)->map = map;
	return (true);
}
