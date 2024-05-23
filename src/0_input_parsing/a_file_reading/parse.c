/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/23 10:49:10 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	free_split(char	**split, bool ret)
{
	int	i;

	i = -1;
	if (!split)
		return (ret);
	while (split[++i])
		free(split[i]);
	free(split);
	return (ret);
}

int	split_len(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

bool	char_is_in(char c, char *seq)
{
	int	i;

	if (!seq)
		return (false);
	i = -1;
	while (seq[++i])
		if (c == seq[i])
			return (true);
	return (false);
}

bool	regex(char *line, char *reg)
{
	int	i;

	if (!line || !reg || !*line || !*reg)
		return (false);
	i = -1;
	while (line[++i])
		if (!char_is_in(line[i], reg))
			return (false);
	return (true);
}

static bool	set_value(char	**value, char	*set)
{
	char	*val;
	int		file;

	val = *value;
	if (!value || val)
		return (false);
	val = ft_strdup(set);
	if (!val)
		return (false);
	if (val[ft_strlen(val) - 1] == '\n')
		val[ft_strlen(val) - 1] = 0;
	if (strlen(val) > 4
		&& !str_is_equal(&(val[strlen(val) - 4]), ".png"))
	{
		logger(LOGGER_WARNING,
			"Invalid texture file extension. Please provide a .png file!");
		return (false);
	}
	file = open(val, O_RDONLY);
	if (file < 0)
	{
		logger(LOGGER_WARNING, "Failed to open texture file!");
		return (false);
	}
	if (DEBUG)
		printf("Texture file set to '%s'\n", val);
	close(file);
	return (true);
}

static bool	set_color(t_color *color, char *color_val)
{
	char	**cols;

	if (!color_val) // TODO: set default color vals to all -1
		return (false);
	cols = ft_split(color_val, ',');
	if (!cols)
		return (false);
	if (split_len(cols) != 3) // TODO: check wether to set default vals when not all rgb is set
		return (free_split(cols, false));
	color->r = ft_atoi(cols[0]);
	if (!(color->r < 256 && color->r >= 0))
		return (free_split(cols, false));
	color->g = ft_atoi(cols[1]);
	if (!(color->g < 256 && color->g >= 0))
		return (free_split(cols, false));
	color->b = ft_atoi(cols[2]);
	if (!(color->b < 256 && color->b >= 0))
		return (free_split(cols, false));
	free_split(cols, NULL);
	if (DEBUG)
		printf("Color set to [%d, %d, %d]\n", color->r, color->g, color->b);
	return (true);
}

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

void	set_player_spawn(char dir)
{
	if (dir == 'N')
		get_player()->spawn_look_dir = (t_vec2){-1, 0};
	else if (dir == 'S')
		get_player()->spawn_look_dir = (t_vec2){1, 0};
	else if (dir == 'E')
		get_player()->spawn_look_dir = (t_vec2){0, 1};
	else if (dir == 'W')
		get_player()->spawn_look_dir = (t_vec2){0, -1};
	else
		logger(LOGGER_WARNING, "Player spawn look dir is not valid dir");
}

bool	parse_map(char **data, t_input_data **input_data, int *i)
{
	int			map_len;
	int			k;
	int			j;
	t_tile_type	***map;

	map_len = 0;
	while ((*i) + map_len < *get_file_len() && data[(*i) + map_len] && regex(data[(*i) + map_len], MAP_TILES))
		map_len++;
	if (map_len < 3)
		return (false);
	map = gc_malloc((map_len + 1) * sizeof(t_tile_type **));
	map[map_len] = NULL;
	k = -1;
	while (data[*i] && regex(data[*i], MAP_TILES) && (*i) - map_len < map_len)
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
				get_player()->spawn_point = (t_vec2){k, j};
				set_player_spawn(data[*i][j]);
				*map[k][j] = FLOOR;
			}
		}
		(*i)++;
	}
	(*input_data)->map = map;
	print_map(map);
	return (true);
}
