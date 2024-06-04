/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:39:02 by jkauker           #+#    #+#             */
<<<<<<< HEAD:src/0_input_parsing/a_file_reading/parse.c
/*   Updated: 2024/06/04 11:16:46 by jkauker          ###   ########.fr       */
=======
/*   Updated: 2024/05/29 09:27:51 by freddy           ###   ########.fr       */
>>>>>>> master:src/1_input_parsing/a_file_reading/parse.c
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	regex(char *line, char *reg);
bool	char_is_in(char c, char *seq);
int		split_len(char **split);
bool	free_split(char	**split, bool ret);
void	set_player_spawn(char dir, t_vec2 pos, t_tile_type ***map);
bool	set_color(t_color *color, char *color_val);
bool	set_value(char	**value, char	*set);

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
<<<<<<< HEAD:src/0_input_parsing/a_file_reading/parse.c
	else if (str_is_equal(split[0], "C")
		&& !set_color(&((*input_data)->ceiling_color), split[1]))
=======
	}
	file = open(*value, O_RDONLY);
	if (file < 0)
	{
		logger(LOGGER_WARNING, "Failed to open texture file!");
		return (false);
	}
	close(file);
	if (DEBUG)
		printf("Texture file set to '%s'\n", *value);
	return (true);
}

static bool	set_color(t_color *color, char *color_val)
{
	char	**cols;
	int		curr_col;

	if (!color_val) // TODO: set default color vals to all -1
>>>>>>> master:src/1_input_parsing/a_file_reading/parse.c
		return (false);
	else if (regex(data[*i], MAP_TILES))
		return (false);
<<<<<<< HEAD:src/0_input_parsing/a_file_reading/parse.c
=======
	if (split_len(cols) != 3) // TODO: check wether to set default vals when not all rgb is set
		return (free_split(cols, false));
	curr_col = ft_atoi(cols[0]);
	if (!(curr_col < 256 && curr_col >= 0))
		return (free_split(cols, false));
	color->r = curr_col;
	curr_col = ft_atoi(cols[1]);
	if (!(curr_col < 256 && curr_col >= 0))
		return (free_split(cols, false));
	color->g = curr_col;
	curr_col = ft_atoi(cols[2]);
	if (!(curr_col < 256 && curr_col >= 0))
		return (free_split(cols, false));
	color->b = curr_col;
	color->a = 255;
	free_split(cols, NULL);
	if (DEBUG)
		printf("Color set to [%d, %d, %d] (0x%X)\n", color->r, color->g, color->b, t_color_to_int(*color));
>>>>>>> master:src/1_input_parsing/a_file_reading/parse.c
	return (true);
}

bool	parse_attributes(char **data, t_input_data **input_data, int *i)
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
		if (!set_values(split, input_data, data, i))
			return (free_split(split, false));
		free_split(split, NULL);
	}
	return (true);
}

int	get_map_len(int *i, char **data)
{
<<<<<<< HEAD:src/0_input_parsing/a_file_reading/parse.c
	int	map_len;

	map_len = 0;
	while (data[(*i) + map_len] && regex(data[(*i) + map_len], MAP_TILES))
		map_len++;
	return (map_len);
=======
	get_player()->spawn_transform.rot = (t_vec2){0, 0};
	if (dir == 'N')
		get_player()->spawn_transform.rot = (t_vec2){-1, 0};
	else if (dir == 'S')
		get_player()->spawn_transform.rot = (t_vec2){1, 0};
	else if (dir == 'E')
		get_player()->spawn_transform.rot = (t_vec2){0, 1};
	else if (dir == 'W')
		get_player()->spawn_transform.rot = (t_vec2){0, -1};
	else
		logger(LOGGER_WARNING, "Player spawn look dir is not valid dir");
>>>>>>> master:src/1_input_parsing/a_file_reading/parse.c
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
		map[++k] = gc_malloc(ft_strlen(data[*i]) * sizeof(t_tile_type *) + 1);
		map[k][ft_strlen(data[*i])] = NULL;
		j = -1;
		while (data[*i][++j])
		{
			map[k][j] = gc_malloc(sizeof(t_tile_type));
			if (data[*i][j] == '0' || data[*i][j] == '1')
				*map[k][j] = (t_tile_type)(data[*i][j] - '0');
			else if (data[*i][j] == ' ')
				*map[k][j] = VOID;
			else
<<<<<<< HEAD:src/0_input_parsing/a_file_reading/parse.c
				set_player_spawn(data[*i][j], (t_vec2){k, j}, map);
=======
			{
				get_player()->spawn_transform.pos = (t_vec2){j, k};
				set_player_spawn(data[*i][j]);
				*map[k][j] = FLOOR;
			}
>>>>>>> master:src/1_input_parsing/a_file_reading/parse.c
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
