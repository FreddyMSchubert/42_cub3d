/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/06/26 13:38:52 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	set_values(char **split, t_input_data **input_data, char **data, int *i)
{
	if (str_is_equal(split[0], "NO")
		&& !set_value(&(*input_data)->no_texture_location, split[1]))
		return (false);
	else if (str_is_equal(split[0], "SO")
		&& !set_value(&(*input_data)->so_texture_location, split[1]))
		return (false);
	else if (str_is_equal(split[0], "WE")
		&& !set_value(&(*input_data)->we_texture_location, split[1]))
		return (false);
	else if (str_is_equal(split[0], "EA")
		&& !set_value(&(*input_data)->ea_texture_location, split[1]))
		return (false);
	else if (str_is_equal(split[0], "F")
		&& !set_color(&((*input_data)->floor_color), split[1]))
		return (false);
	else if (str_is_equal(split[0], "C")
		&& !set_color(&((*input_data)->ceiling_color), split[1]))
		return (false);
	else if (regex(data[*i], MAP_TILES))
		return (false);
	return (true);
}

bool	parse_attributes(char **data, t_input_data **input_data, int *i)
{
	char	**split;

	if (!data[(*i)--])
		return (true);
	while (data[++(*i)] && !regex(data[*i], MAP_TILES))
	{
		if (data[*i][0] == 0)
			continue ;
		split = ft_split(data[*i], ' ');
		if (!split || split_len(split) != 2) // TODO: when we have F or C color not only seperated by comma but also by space it stops here
			return (free_split(split, true));
		if (!set_values(split, input_data, data, i))
			return (free_split(split, false));
		free_split(split, NULL);
	}
	return (true);
}

int	get_map_len(int *i, char **data)
{
	int	map_len;

	map_len = 0;
	while (data[(*i) + map_len] && regex(data[(*i) + map_len], MAP_TILES))
		map_len++;
	return (map_len);
}

t_tile_type	***make_map(int map_len, int *i, char **data)
{
	t_tile_type	***map;
	int			k;
	int			j;

	map = gc_malloc((map_len + 1) * sizeof(t_tile_type **));
	map[map_len] = NULL;
	k = -1;
	while (++(*i) && data[*i] && regex(data[*i], MAP_TILES) && map_len--)
	{
		map[++k] = gc_malloc((ft_strlen(data[*i]) + 1) * sizeof(t_tile_type *));
		map[k][ft_strlen(data[*i])] = NULL;
		j = -1;
		while (data[*i][++j])
		{
			map[k][j] = gc_malloc(sizeof(t_tile_type));
			if (data[*i][j] == '0' || data[*i][j] == '1')
				*(map[k][j]) = (t_tile_type)(data[*i][j] - '0');
			else if (data[*i][j] == ' ')
				*(map[k][j]) = VOID;
			else if (data[*i][j] == 'G' && !set_goal((t_vec2){j, k}, map))
				return (NULL);
			else if ((data[*i][j] == 'H' || data[*i][j] == 'V') && !set_door((t_vec2){j, k}, map, data[*i][j]))
				return (NULL);
			else if ((data[*i][j] == 'w' || data[*i][j] == 'e' || data[*i][j] == 'a' || data[*i][j] == 'f') && !set_orb((t_vec2){j, k}, map, data[*i][j]))
				return (NULL);
			else if (data[*i][j] == 'K' && !set_key((t_vec2){j, k}, map))
				return (NULL);
			else if (char_is_in(data[*i][j], "NSEW") && !set_entity_spawn(data[*i][j], (t_vec2){j, k}, map))
				return (NULL);
		}
	}
	return (map);
}

bool	parse_map(char **data, t_input_data **input_data, int *i)
{
	int			map_len;
	t_tile_type	***map;

	map_len = get_map_len(i, data);
	if (map_len < 3)
		return (false);
	map = gc_malloc((map_len + 1) * sizeof(t_tile_type **));
	map[map_len] = NULL;
	(*i)--;
	(*input_data)->map = make_map(map_len, i, data);
	return (true);
}
