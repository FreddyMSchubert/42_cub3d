/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/07 13:47:51 by freddy           ###   ########.fr       */
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
	else if (str_is_equal(split[0], "FO") && !set_fog(split[1], input_data))
		return (false);
	else if (str_is_equal(split[0], ">"))
		return (print_map_line(split), true);
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
		if (!split || (split_len(split) != 2 && data[*i][0] != '>'))
			return (free_split(split, true));
		if (!set_values(split, input_data, data, i))
			return (free_split(split, false));
		free_split(split, NULL);
	}
	return (true);
}

static inline bool	check_element_at_pos(t_scale s, t_tile_type ***map, \
										char **d, int i)
{
	if (d[i][s.x] == '0' || d[i][s.x] == '1')
		*(map[s.y][s.x]) = (t_tile_type)(d[i][s.x] - '0');
	else if (d[i][s.x] == ' ')
		*(map[s.y][s.x]) = VOID;
	else if (d[i][s.x] == 'G' && !set_goal((t_vec2){s.x, s.y}, map))
		return (false);
	else if (d[i][s.x] == 'h' && !set_health((t_vec2){s.x, s.y}, map))
		return (false);
	else if ((d[i][s.x] == 'H' || d[i][s.x] == 'V') && \
					!set_door((t_vec2){s.x, s.y}, map, d[i][s.x]))
		return (false);
	else if ((d[i][s.x] == 'w' || d[i][s.x] == 'e' || d[i][s.x] == 'a'
	|| d[i][s.x] == 'f') && !set_orb((t_vec2){s.x, s.y}, map, d[i][s.x]))
		return (false);
	else if ((d[i][s.x] == 'q' || d[i][s.x] == 'r' || d[i][s.x] == 'd' || d[i] \
	[s.x] == 's' || d[i][s.x] == 'u' || d[i][s.x] == 'i' || d[i][s.x] == 'o' \
	|| d[i][s.x] == 'p') && !set_blight((t_vec2){s.x, s.y}, map, d[i][s.x]))
		return (false);
	else if (d[i][s.x] == 'K' && !set_key((t_vec2){s.x, s.y}, map))
		return (false);
	else if (d[i][s.x] == 'B' && !set_boss((t_vec2){s.x, s.y}, map))
		return (false);
	return (!(char_is_in(d[i][s.x], "NSEW") && !set_entity_spawn(d[i][s.x], \
				(t_vec2){s.x, s.y}, map)));
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
			if (!check_element_at_pos((t_scale){j, k}, map, data, *i))
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
